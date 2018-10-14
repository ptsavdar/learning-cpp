//
// Created by panos on 16/06/18.
//

#include <iostream>
using namespace std;

// Create a char string and output it
// Output all the chars with a for loop
// Output all the chars with a while(true) loop

int _mainca() {
    char text[]{"hello"};

    for (int i = 0; i < sizeof(text); i++) {
        cout << i << ": " << text[i] << endl;
    }

    int k = 0;

    while (true) {

        if (text[k] == 0)
            break;

        cout << text[k] << flush;

        k++;
    }
}