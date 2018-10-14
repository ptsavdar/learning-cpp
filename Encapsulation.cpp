//
// Created by panos on 16/06/18.
//

#include <iostream>
using namespace std;

class Frog {
private:
    string name;

public:
    explicit Frog(string name): name{move(name)} {}
    string getName() {return name;}
};


int mainencap() {
    Frog frog("Freddy");

    return 0;
}