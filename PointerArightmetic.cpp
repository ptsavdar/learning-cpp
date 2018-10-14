//
// Created by panos on 16/06/18.
//

#include <iostream>
using namespace std;

int _mainpar() {
    const int NSTRINGS{5};

    string texts[NSTRINGS]{"one", "two", "three", "four", "five"};

    string *pTexts = texts;

    cout << *pTexts << endl;

    string *pEnd = &texts[NSTRINGS];

    double elements {(double)(pEnd - pTexts)};

    cout << elements << endl;

    return 0;
}