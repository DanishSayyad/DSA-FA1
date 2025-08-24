#include <SFML/Graphics.hpp>
using namespace sf;

enum States {DEFAULT, SELECTED, MOVING};

// Base class for objects in the simulation
class Object {
    public:
        Vector2f position, velocity, acceleration;
};

// Represents an individual element in the sorting visualization
class Element : public Object {
    private:
        short state, radius;
        int value;
        CircleShape body;
        Text text;
    public:
        Element();
        Element(int, int, int, int);
        void setValue(int v);
        void setColor(short);
        void move(float, float);
        void draw(RenderWindow *);
};

class Radix {
    private:
        // Pointer to the SFML RenderWindow
        RenderWindow *window;

        // Background color for the window
        Color bgColor;

        // Text for displaying information
        Text text;

    public:
        // Initializes all the variables needed for Radix Sort visualization
        Radix();

        // Destructor to free up memory
        ~Radix();

        // Main simulation loop
        void simulate(int, int, int);
};
