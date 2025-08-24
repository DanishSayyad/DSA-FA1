#include <ctime>
#include <cstdlib>

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int randomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void populateRandom(int arr[], int n, int min, int max) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < n; ++i) {
        arr[i] = randomInt(min, max);
    }
}
