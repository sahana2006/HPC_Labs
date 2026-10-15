
#include <iostream>
#include <omp.h>

using namespace std;

// Simulates f(i) taking i milliseconds.
void f(int i) {
    // Actual computation would go here.
    // This sleep simulates the execution time.
    // Avoid using sleep for precise performance benchmarking.
    double start = omp_get_wtime();

    while ((omp_get_wtime() - start) < i / 1000.0) {
        // Busy wait
    }
}

int main() {
    int n;

    cout << "Enter n: ";
    cin >> n;

    // 1. Static scheduling
    cout << "\n--- schedule(static) ---\n";

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(2)
    {
        int tid = omp_get_thread_num();

        #pragma omp for schedule(static)
        for (int i = 1; i < n; i++) {
            f(i);
        }

        #pragma omp for schedule(static)
        for (int i = 1; i < n; i++) {
            f(n - i);
        }

        #pragma omp barrier
        #pragma omp single
        cout << "Both threads completed.\n";
    }

    cout << "Time: " << omp_get_wtime() - start
         << " seconds\n";


    // 2. Static scheduling with chunk size 1
    cout << "\n--- schedule(static, 1) ---\n";

    start = omp_get_wtime();

    #pragma omp parallel num_threads(2)
    {
        #pragma omp for schedule(static, 1)
        for (int i = 1; i < n; i++) {
            f(i);
        }

        #pragma omp for schedule(static, 1)
        for (int i = 1; i < n; i++) {
            f(n - i);
        }
    }

    cout << "Time: " << omp_get_wtime() - start
         << " seconds\n";


    // 3. Dynamic scheduling with chunk size 1
    cout << "\n--- schedule(dynamic, 1) ---\n";

    start = omp_get_wtime();

    #pragma omp parallel num_threads(2)
    {
        #pragma omp for schedule(dynamic, 1)
        for (int i = 1; i < n; i++) {
            f(i);
        }

        #pragma omp for schedule(dynamic, 1)
        for (int i = 1; i < n; i++) {
            f(n - i);
        }
    }

    cout << "Time: " << omp_get_wtime() - start
         << " seconds\n";


    // 4. Static scheduling with nowait
    cout << "\n--- schedule(static) with nowait ---\n";

    start = omp_get_wtime();

    #pragma omp parallel num_threads(2)
    {
        #pragma omp for schedule(static) nowait
        for (int i = 1; i < n; i++) {
            f(i);
        }

        #pragma omp for schedule(static)
        for (int i = 1; i < n; i++) {
            f(n - i);
        }
    }

    cout << "Time: " << omp_get_wtime() - start
         << " seconds\n";

    return 0;
}
