#include <iostream>
#include "visualizer.h"

using namespace std;

int main(int argc, char *argv[]) {
    
    if(argc < 2) {
        cout << "Usage: sort <elements> [min] [max]\n\t";
        cout << "elements: Number of elements to sort\n\t";
        cout << "min: Minimum value of elements (default 1)\n\t";
        cout << "max: Maximum value of elements (default 100)\n";
        return 1;
    }

    int num = atoi(argv[1]);
    if(num < 1) {
        cout << "Number of elements must be at least 1\n";
        return 1;
    }

    int min = 1, max = 100;
    if(argc == 3) min = atoi(argv[2]);
    if(argc == 4) max = atoi(argv[3]);

    Radix viz;

    viz.simulate(num, min, max);
    
    return 0;
}
