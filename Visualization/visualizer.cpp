#include <iostream>
#include "visualizer.h"

using namespace std;

Radix::Radix() {
    window = new RenderWindow(VideoMode(1200, 900), "Sorting Visualizer");
    window->setFramerateLimit(60);
    bgColor = Color(33, 37, 41);
    if (!font.loadFromFile("assets/opensans.ttf")) {
        cout << "Error loading font\n";
    }
    text.setFont(font);
    text.setCharacterSize(24);
}

Radix::~Radix() {
    delete window;
}

void Radix :: simulate(int n) {
    Event event;
    while(window->isOpen()) {
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window->close();
            }
        }

        window->clear(bgColor);
        window->display();
    }
}
