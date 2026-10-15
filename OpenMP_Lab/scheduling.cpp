
#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    const int N = 20;

    omp_set_dynamic(0);
    omp_set_num_threads(4);

    cout << "Default scheduling demonstration\n";

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        printf("Thread %d executes iteration %d\n",
               omp_get_thread_num(), i);
    }

    return 0;
}
