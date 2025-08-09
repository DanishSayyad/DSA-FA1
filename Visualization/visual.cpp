#include <SFML/Graphics.hpp>
#include<iostream>

using namespace sf;
using namespace std;

RenderWindow window(VideoMode(512, 512), "Sorting Comparisions");

int main() {
    
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