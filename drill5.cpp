//
// Created by panos on 28/05/18.
//

#include <iostream>
using namespace std;

class Bad_input: exception {};

int area (int width, int height);

int drill5() {
    try {
        int x0 = area(-7, 8);
        cout << x0 << endl;
    } catch (Bad_input& e) {
        cerr << "Bad input was given" << endl;
    }
    return 0;
}

int area(int width, int height) {
    if (width <= 0 || height <= 0) throw Bad_input{};
    return width * height;
}
