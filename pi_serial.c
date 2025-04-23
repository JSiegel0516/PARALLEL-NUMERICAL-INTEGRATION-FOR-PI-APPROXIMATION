#include <stdio.h>            // header file for built-in standard i/p & o/p functions
#include <stdlib.h>           // header file for standard library functions
#include <math.h>             // header file to get the value of PI so we can measure how close
#include "timer.h"

//Helper function for x * x
double square(double x)
{
    return x * x;
}

//computes delta x
double deltax(int n)
{
    return 1.0 / n;
}

double fofx(double x)
{
    return 4.0/(1.0 + square(x));
}

double PIcalculate(int n)
{
    double x, total;
    x = deltax(n);
    total = fofx(0.0) + fofx(1.0); //upper and lower bounds
    int i = 1;
    while(i < n)
    {
        if(i % 2 == 0)
        {
            total += 2 * fofx(i * x);
        }
        else 
        {
            total += 4 * fofx(i * x);
        }
        i++;
    }
    return total * x / 3.0;

}


int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Incorrect Usage. Run as ./pi_serial <number (1-10)>\n");
        exit(EXIT_FAILURE);
    }
    int num = atoi(argv[1]);
    if(num < 1 || num > 10)
    {
        fprintf(stderr, "The number must be inbetween 1 and 10\n");
        exit(EXIT_FAILURE);
    }
    double start, end, elapsed;
    GET_TIME(start);
    int n = pow(10,num);
    double error = M_PI - PIcalculate(n);
    GET_TIME(end);
    elapsed = end - start;
    printf("Estimated value of Pi: %.15f\n", PIcalculate(n));
    printf("Exact value of Pi: %.15f\n", M_PI);
    printf("Computation Error: %.15f\n", error);
    printf("The total elapsed time is %e seconds \n", elapsed);
    return 0;
}