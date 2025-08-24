#include <iostream>
#include "visualizer.h"
#include "arrutil.h"

using namespace std;

// Global font for text rendering
Font *fontGlobal;

Color colors[] = {Color(118, 245, 245), Color(), Color()};

Radix::Radix() {
    window = new RenderWindow(VideoMode(1700, 900), "Radix Sort Visualizer");
    window->setFramerateLimit(60);
    bgColor = Color(43, 47, 51);
    fontGlobal = new Font();
    if (!(*fontGlobal).loadFromFile("assets/opensans.ttf"))
        cout << "Error loading font\n";
    text.setFont(*fontGlobal);
    text.setCharacterSize(24);
}

Radix::~Radix() {
    delete window;
    delete fontGlobal;
}

void Radix :: simulate(int n, int min, int max) {

    int arr[n];
    populateRandom(arr, n, min, max);
    Element elements[n];

    float rad = 1700 / (4 * n);
    for(int i = 0; i < n; i++) {
        float curr = rad + (i * rad * 4);
        elements[i] = Element(arr[i], rad, (int)curr, 900/3 - rad);
    }

    Event event;
    Element num(13, 40, 100, 100);
    while(window->isOpen()) {
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window->close();
            }
        }

        window->clear(bgColor);
        for(int i = 0; i < n; i++) {
            elements[i].draw(window);
        }
        window->display();
    }
}

Element::Element() {
    position = Vector2f(0, 0);
    velocity = Vector2f(0, 0);
    acceleration = Vector2f(0, 0);
    state = DEFAULT;
    body = CircleShape(radius);
    body.setPosition(position);
    text.setFont(*fontGlobal);
    setValue(value);
    text.setFillColor(Color::Black);
}

Element::Element(int val, int r, int x, int y) {
    value = val;
    radius = r;
    position = Vector2f(x, y);
    velocity = Vector2f(0, 0);
    acceleration = Vector2f(0, 0);
    state = DEFAULT;
    body = CircleShape(radius);
    body.setPosition(position);
    text.setFont(*fontGlobal);
    setValue(value);
    text.setFillColor(Color::Black);
}

void Element::draw(RenderWindow *win) {
    int thickness = radius / 8;
    CircleShape border = CircleShape(radius + thickness);
    border.setFillColor(Color::Black);
    border.setPosition(body.getPosition().x - thickness, body.getPosition().y - thickness);
    
    Vector2f textPos = body.getPosition();
    textPos.x += radius - text.getGlobalBounds().width / 2;
    textPos.y += radius - text.getGlobalBounds().height / 2 - (radius / 8);
    text.setPosition(textPos);
    setColor(state);

    win->draw(border);
    win->draw(body);
    win->draw(text);
}

void Element::setColor(short c) {
    body.setFillColor(colors[c]);
}

void Element::setValue(int v) {
    value = v;
    text.setString(to_string(value));
    int size;
    if(value < 10 && value >= 0) size = radius;
    else if(value < 100 && value >= 10) size = radius / 1.4;
    else size = radius / 1.6;
    text.setCharacterSize(size);
}
