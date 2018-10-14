//
// Created by panos on 15/06/18.
//

#include <iostream>
#include <vector>

using namespace std;

int _mainv() {
    int numberCats = 5;

    float t = 1.1;
    float w = 1.1;

    short int v[5];
    vector<int> v2{1,2,3,4,5,6};

    cout << sizeof(v) / sizeof(v[0]) << endl;

    cout << v2[5] << endl;

    if (t == (float)1.1) cout << "Hello floats!" << endl;

    cout << "Hello cats " << numberCats << endl;

    return 0;
}