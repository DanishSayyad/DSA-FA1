#include <ctime>
#include <cstdlib>

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void populateRandom(int arr[], int n) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % (n + 1);
    }
}
