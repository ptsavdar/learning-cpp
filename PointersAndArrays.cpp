//
// Created by panos on 16/06/18.
//

#include <iostream>
using namespace std;

int _mainpa() {
    string texts[]{"one", "two", "three"};

    string *pTexts = texts;

    int sz = sizeof(texts) / sizeof(string);

    for(unsigned int i=0; i < sz; i++) {
        cout << pTexts[i] << " " << flush;
    }

    cout << endl;

    for (unsigned int i = 0; i < sz; i++) {
        cout << *pTexts << " " << flush;

        pTexts++;
    }

    cout << endl;

    string *pElement = &texts[0];
    string *pEnd = &texts[sz - 1];

    while(pElement <= pEnd) {
        cout << *pElement << " " << flush;

        pElement++;
    }

    return 0;
}
