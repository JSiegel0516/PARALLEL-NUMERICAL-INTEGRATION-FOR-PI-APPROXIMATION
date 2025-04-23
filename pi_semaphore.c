#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include "timer.h"

double total_sum = 0.0; // Global variable for total sum
sem_t sem; // Semaphore declaration
double delta_x;
int thread_count;
double low, high;
double N = 6400000.0;

double fofx(double x)
{
    return 4.0 / (1.0 + x * x);
}

void* sum(void* X)
{
    long thread_id = (long) X;
    double lsum = 0.0;
    double localLow = thread_id * (N / thread_count) * (1.0 / N);
    double localhigh = (thread_id + 1) * (N / thread_count) * (1.0 / N);
    int i = thread_id * (N / thread_count);
    while (i < (thread_id + 1) * (N / thread_count))
    {
        double x = i * (1.0 / N);
        if (i == N || i == 0)
        {
            i++;
            continue;
        }
        if (i % 2 == 0)
        {
            lsum += 2 * fofx(x);
        }
        else
        {
            lsum += 4 * fofx(x);
        }
        i++;
    }
    sem_wait(&sem);
    total_sum += lsum;
    sem_post(&sem);
    return NULL;
}

double PIcalc()
{
    total_sum = fofx(0.0) + fofx(1.0); // upper and lower bounds
    pthread_t threads[thread_count];
    sem_init(&sem, 0, 1);
    for (long thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&threads[thread], NULL, sum, (void*)thread);
    }
    for (long thread = 0; thread < thread_count; thread++)
    {
        pthread_join(threads[thread], NULL);
    }
    sem_destroy(&sem);
    return total_sum * (1.0 / N) / 3.0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Incorrect Usage. Run as ./pi_semaphore <number_of_threads>\n");
        exit(EXIT_FAILURE);
    }
    thread_count = atoi(argv[1]);
    if (thread_count < 1)
    {
        fprintf(stderr, "The number of threads must be at least 1\n");
        exit(EXIT_FAILURE);
    }

    //int thread_counts[] = {1, 2, 4, 8, 16}; // for testing purposes
    //int count = sizeof(thread_counts) / sizeof(thread_counts[0]);
    //double time = 0.0;
    double start,finish,elapsed;
    GET_TIME(start);
    double pisimpsons = PIcalc();
    GET_TIME(finish);
    elapsed = finish - start;
    double error = M_PI - pisimpsons;
    printf("Performance Evaluation using Semaphore method:\n");
    printf("Number of iterations N = %f\n\n", N);
    printf("Estimated value of Pi: %.15f\n", pi_estimate);
    printf("Computation Error: %.15f\n", error);
    printf("Elapsed time: %e seconds\n", elapsed);


    return 0;
}
