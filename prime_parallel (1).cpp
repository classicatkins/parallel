//#include <iostream>
//#include <cmath>
//#include <omp.h>
using namespace std;

void gen_numbers(long int[], long int);
int count_prime(long int[], long int, int);
bool is_prime(long int);

int main(int argc, char**argv)
{
    //comand-line integer input
    int thread_count = atoi(argv[1]);
    cout << thread_count << endl;
    long int n = 1000000;
    long int* numbers = new long int[n];

    gen_numbers(numbers, n);
    //start timer
    double start = omp_get_wtime();
    int count = count_prime(numbers, n, thread_count);
    //end timer
    double end = omp_get_wtime();
    //print time as end - start
    cout << "Time of algorithm:" << end - start << endl;

    cout << "Total number of primes: " << count << endl;

    return 0;
}

void gen_numbers(long int numbers[], long int size)
{
    for(int i = 0; i < size; i++) {
        numbers[i] = i;
    }
}

int count_prime(long int numbers[], long int size, int thread_count)
{
//sets count to zero
    int count = 0;
// reduction makes sure threads deliver count at different times
    #pragma omp parallel for reduction(+:count) num_threads(thread_count)
    for(int i = 0; i < size; i++) 
    {
//threads count how many prime numbers are in their section at same time
        if(is_prime(numbers[i])) {
            count++;
        }
    }
    return count;
}

bool is_prime(long int n) {
    if (n < 2)
        return false;
    for(int i=2; i<sqrt(n); i++)
    {
        if(n % i == 0) {
            return false;
        }
    }
    return true;
}

