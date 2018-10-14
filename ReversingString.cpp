//
// Created by panos on 16/06/18.
//

#include <iostream>
using namespace std;

int _mainrs() {
    char text[]{"hello"};

    int sz = sizeof(text) - 1;

    char *pStart = text;
    char *pEnd = text + sz - 1;

    for (int i = sz - 1; i >= 0; --i) {
        cout << text[i] << flush;
    }

    cout << endl;

    while(pStart <= pEnd) {
        cout << *pEnd << flush;

        pEnd--;
    }

    return 0;
}
