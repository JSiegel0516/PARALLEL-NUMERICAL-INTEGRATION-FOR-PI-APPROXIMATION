
# Project Title

A brief description of what this project does and who it's for

# PARALLEL-NUMERICAL-INTEGRATION-FOR-PI-APPROXIMATION

# 🧮 Pi Approximation using Simpson’s Rule (Serial & Parallel in C)

This project estimates the value of π using **Simpson’s Rule**, implemented in C through:
- 🔓 Serial computation
- 🧵 Multithreading with **mutexes**
- 🚦 Multithreading with **semaphores**

The goal is to compare computational accuracy, synchronization strategies, and performance across implementations.

---

## 📂 File Descriptions

### `pi_mutex.c`
Multi-threaded approximation of π using **pthread mutex locks**.

- Threads compute chunks of the integral
- A mutex ensures safe updates to a shared total
- Measures runtime and numerical error

**Usage**:
./pi_mutex <number_of_threads>


### `pi_semaphore.c`
Same as pi_mutex.c, but uses POSIX semaphores (sem_t) instead of mutexes.

- Compares semaphore vs mutex synchronization
- Threads safely update a global sum using semaphore control
- Outputs estimated π, error, and elapsed time

**Usage**:

./pi_semaphore <number_of_threads>

**Usage**:

./pi_mutex <number_of_threads>

### `pi_serial.c`
A serial implementation of π estimation using Simpson’s Rule.

- No threads or synchronization involved
- Ideal for performance baseline
- Accepts n as input, where N = 10^n intervals

**Usage**:

./pi_serial <n>

**Usage**:

./pi_mutex <number_of_threads>

### `test.c`
A minimal, clean serial version of the π approximation.

- Uses clearly separated loops for even and odd terms
- Great for correctness validation
- Runs without timing metrics

**Usage**:

./test <n>

### MATH BACKGROUND
The programs estimate π by computing the integral of the function:
- f(x) = 4 / (1 + x^2)
Using Simpson’s Rule, which approximates an integral as:
- h = (b - a) / n
- Integral ≈ h/3 × [f(x0) + 4f(x1) + 2f(x2) + ... + f(xn)]

### Compile
- gcc -o pi_mutex pi_mutex.c -lpthread -lm
- gcc -o pi_semaphore pi_semaphore.c -lpthread -lm
- gcc -o pi_serial pi_serial.c -lm
- gcc -o test test.c -lm

