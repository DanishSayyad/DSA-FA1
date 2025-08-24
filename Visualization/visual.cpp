#include <iostream>
#include "visualizer.h"

using namespace std;

int main(int argc, char *argv[]) {
    
    if(argc != 2) {
        cout << "Usage: sort <number of elements>\n";
        return 1;
    }

    Radix viz;

    viz.simulate(atoi(argv[1]));
    
    return 0;
}
