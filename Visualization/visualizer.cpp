#include <iostream>
#include "visualizer.h"
#include "arrutil.h"
#include <cmath>
#include <string>

using namespace std;

// Global font for text rendering
Font *fontGlobal;

Color colors[] = {Color(118, 245, 245), Color(255, 205, 89), Color(255, 204, 204), Color(155, 156, 152)};

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

void Element::move(float x, float y) {
    position.x = x;
    position.y = y;
    body.setPosition(position);
}

Radix::~Radix() {
    delete window;
    delete fontGlobal;
}

// Node constructor
Node::Node(const Element &e) : data(e), next(nullptr) {}

Queue::Queue() : head(nullptr), tail(nullptr), count(0) {}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

bool Queue::isEmpty() const {
    return head == nullptr;
}

void Queue::enqueue(Element e) {
    Node *newNode = new Node(e);
    if (tail) {
        tail->next = newNode;
        tail = newNode;
    } else {
        head = tail = newNode;
    }
    count++;
}

void Queue::display(RenderWindow *w, int rad) {
    Node *ptr = head;
    int c = 0;
    while(ptr) {
        (ptr->data).move(position.x, position.y + (c * 2.5 * rad));
        c++;
        (ptr->data).setColor(MOVED);
        (ptr->data).draw(w);
        ptr = ptr->next;
    }
}

Element Queue::dequeue() {
    if (isEmpty()) {
        std::cout << "Queue underflow!\n";
        return Element(); // return dummy element
    }
    Node *temp = head;
    Element result = temp->data;
    head = head->next;
    if (!head) {
        tail = nullptr;
    }
    delete temp;
    count--;
    return result;
}

Bucket :: Bucket(RenderWindow *window, int r) {
    rad = r;
    Object :: position = Vector2f(0, 400);
    for(int i = 0; i < 10; i++) {
        bucket[i].position.x = (i * 170) + (170  / 2) - rad;
        bucket[i].position.y = 440;
    }
    return;
}

void Bucket::draw(RenderWindow *window) {
    Text text;
    text.setFont(*fontGlobal);
    text.setCharacterSize(20);
    text.setFillColor(Color::White);
    for(char ch = '0'; ch <= '9'; ch++) {
        text.setString(ch);
        text.setPosition(((ch - 48) * 170) + (170 / 2), position.y);
        window->draw(text);
    }
    display(window);
}

void Bucket::display(RenderWindow *win) {
    for(int i = 0; i < 10; i++) {
        bucket[i].display(win, rad);
    }
}

int Element :: getValue() {
    return value;
}

int maxDigit(int arr[], int n) {
    int max = arr[0];
    for(int i = 1; i < n; i++) {
        if(arr[i] > max) max = arr[i];
    }
    int count = 0;
    for( ; max; count++) {
        max /= 10;
    }
    return count;
}

Caption :: Caption() {
    cap.setFont(*fontGlobal);
    cap.setFillColor(Color::White);
    cap.setCharacterSize(24);
    cap.setPosition(600, 730);
    cap.setString("");
}

void Caption::say(string t, RenderWindow *window) {
    int len = t.length();
    cap.setPosition((1700/2) - (len*5), 600);
    cap.setString(t);
    display(window);
    window->display();
    string cmd = "espeak -v en+f2 \"" + t + "\"";
    system(cmd.c_str());
    cap.setString(" ");
}

void Caption::display(RenderWindow *w) {
    w->draw(cap);
}

Element Bucket :: pop() {
    Element temp;
    for(int i = 0; i < 10; i++) {
        if(bucket[i].isEmpty()) {
            continue;
        }
        temp = bucket[i].dequeue();
        temp.setColor(DEFAULT);
        break;
    }
    return temp;
}

void Radix :: simulate(int n, int min, int max) {

    int arr[n];
    populateRandom(arr, n, min, max);

    int maxD = maxDigit(arr, n);

    Element elements[n];
    int selected = 0, digit = 1;
    bool start = false, init = false, over = false;

    Tray tray(elements, arr, n);
    Bucket *bucket = NULL;
    Caption sub;

    Event event;

    while(window->isOpen()) {
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window->close();
            }

            // spacebar detection
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                if(!over)
                if(!start) {
                    if(!init) {
                        sub.say("Let's start with our Radix Sort, press space to start", window);
                        init = true;
                    }
                    else {
                        tray.position = Vector2f(0, 200);
                        selected = 0;
                        tray.e[selected].setColor(SELECTED);
                        start = true;
                        delete bucket;
                        bucket = new Bucket(window, tray.rad);
                        
                        if(digit == 1)
                        sub.say("Let's start with units place. We will look at our digits in the number.", window);
                        if(digit == 1)
                        sub.say("\nWe will make 10 buckets, numbered 0 to 9", window);
                    }
                }
                else {
                    int num = (tray.e[selected].getValue() % (int)pow(10, digit)) / (int)pow(10, digit - 1);
                    bucket->bucket[num].enqueue(tray.e[selected]);
                    bucket->display(window);
                    tray.e[selected].setColor(DONE);
                    string prestr, numb, poststr, final;
                    numb = to_string(tray.e[selected].getValue());
                    final = " so it will go in bucket " + to_string(num);
                    switch(selected) {
                        case 0:
                            prestr = "The first number is ";
                            poststr = " and the digit we want is " + to_string(num);
                            sub.say(prestr + numb + poststr + final, window);
                            break;
                        case 1:
                            prestr = "The next number is ";
                            poststr = " and the digit we want is " + to_string(num);
                            sub.say(prestr + numb + poststr + final, window);
                            break;
                        default:
                            sub.say(to_string(num), window);
                    }
                    selected++;
                    if(selected >= n) {
                        selected = 0;
                        start = false;
                        if(++digit > maxD) over = true;
                        if(!over) {
                            sub.say("The new array will be made from the buckets.", window);
                            sub.say("\nFirst, bucket number 0 will be emptied.", window);
                            sub.say("\n\nThen, the next bucket will be emptied.", window);
                            sub.say("\n\n\nAnd so on!", window);
                            if(digit > 1)
                                sub.say("\n\n\n\nThe array will be sorted relative to the digit we considered.", window);
                            string place;
                            switch(digit) {
                                case 2:
                                    place = "tens place.";
                                    break;
                                case 3:
                                    place = "hundreds place.";
                                    break;
                                default:
                                    place = "next digit.";
                            }
                            sub.say("\n\n\n\n\nNow, let's move onto the " + place, window);
                        }
                        for(int i = 0; i < n; i++) {
                            tray.e[i] = bucket->pop();
                        }
                    }
                    tray.e[selected].setColor(SELECTED);
                    
                }
                else {
                    sub.say("The array is sorted.", window);
                    window->close();
                }
            }
        }

        window->clear(bgColor);
        tray.updatePos();
        tray.drawTray(window);
        if(bucket)
            bucket->draw(window);
        sub.display(window);
        window->display();
    }
}
