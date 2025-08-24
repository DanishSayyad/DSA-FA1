#include <SFML/Graphics.hpp>
using namespace sf;

enum States {DEFAULT, COMPARE, MOVING};

// A represention of an individual element in the array being sorted
struct element {
    short state, radius;
    int value;
};

class Radix {
    private:
        // Pointer to the SFML RenderWindow
        RenderWindow *window;

        // Background color for the window
        Color bgColor;

        // Font and text for displaying information
        Font font; Text text;
    public:
        // Initializes all the variables needed for Radix Sort visualization
        Radix();

        // Destructor to free up memory
        ~Radix();

        // Main simulation loop
        void simulate(int);
};
