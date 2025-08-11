#include <SFML/Graphics.hpp>
#include<iostream>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

void populateRandom(int[], int);
int partition(int[], int, int);
void quickSort(int[], int, int);

RenderWindow window(VideoMode(1200, 800), "Sorting Visualizer");

int main() {
    
    const int n = 200;
    int arr1[n];

    populateRandom(arr1, n);
    int arr2[n];
    for (int i = 0; i < n; ++i)
        arr2[i] = arr1[i];
    
    Event event;
    
    while(window.isOpen()) {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
    }

    return 0;
}

void populateRandom(int arr[], int n) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % (n + 1);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
