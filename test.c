#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

double compute_pi(int N) {
    double h = 1.0 / N;
    double sum = f(0.0) + f(1.0);
    for (int i = 1; i < N; i += 2) {
        sum += 4.0 * f(i * h);
    }
    for (int i = 2; i < N - 1; i += 2) {
        sum += 2.0 * f(i * h);
    }
    return sum * h / 3.0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of intervals (1-10)>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 1 || n > 10) {
        fprintf(stderr, "Error: The argument must be a number between 1 and 10.\n");
        return 1;
    }

    int N = pow(10, n);
    double pi_estimate = compute_pi(N);
    double pi_exact = M_PI;
    double error = pi_exact - pi_estimate;

    printf("Estimated value of Pi: %.15f\n", pi_estimate);
    printf("Exact value of Pi: %.15f\n", pi_exact);
    printf("Computation Error: %.15f\n", error);

    return 0;
}
