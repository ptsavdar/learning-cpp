//
// Created by panos on 16/06/18.
//

#include <iostream>
using namespace std;

class Animal {
public:
    void speak() { cout << "Grreee" << endl; }
};

class Cat: public Animal {
public:
    void jump() { cout << "Cat jumping!" << endl; }
};

class Tiger: public Cat {
public:
    void attack() { cout << "Attacking!" << endl; }
};

int maininheritance() {
    Animal a;
    a.speak();

    Cat c;
    c.speak();
    c.jump();

    Tiger t;
    t.attack();
    t.speak();

    return 0;
}