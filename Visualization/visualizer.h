#include <SFML/Graphics.hpp>

using namespace sf;

enum States {DEFAULT, SELECTED, MOVED, DONE};

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
        int getValue();
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

class Tray;

struct Node {
    Element data;
    Node *next;
    Node(const Element &e);
};
class Queue : public Object {
private:
    int count;
    Node *head;
    Node *tail;

public:
    Queue();
    ~Queue();

    bool isEmpty() const;
    void enqueue(Element e);
    void display(RenderWindow *w, int rad);
    Element dequeue();
};

class Bucket : public Object {
    private:
        int rad;
    public:
        Queue bucket[10];
        Bucket(RenderWindow *window, int r);
        void draw(RenderWindow *window);
        void display(RenderWindow *win);
        Element pop();
};

class Tray : public Object {
    private:
    int len;
    public:
        int rad;
        Element *e;
        Tray(Element arr[], int a[], int l) {
            Object::position = Vector2f(0, 300);
            e = arr;
            len = l;
            rad = 1700 / (4 * len);
            for(int i = 0; i < len; i++) {
                float curr = rad + (i * rad * 4);
                e[i] = Element(a[i], rad, (int)curr, position.y);
                e[i].setColor(DEFAULT);
            }
        }

        void updatePos() {
            for(int i = 0; i < len; i++) {
                float curr = rad + (i * rad * 4);
                e[i].move((int)curr, position.y);
            }
            return;
        }

        void drawTray(RenderWindow *win) {
            for(int i = 0; i < len; i++) {
                e[i].draw(win);
            }
        }
};

class Caption {
    private:
        Text cap;
    public:
        Caption();
        void say(std::string, RenderWindow *window);
        void set(std::string);
        void display(RenderWindow *w);
};
