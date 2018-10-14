//
// Created by panos on 16/06/18.
//

#include <iostream>
using namespace std;

void manipulate(double &value) {
    value = 10.0;
    cout << "Value of double in manipulate: " << value << endl;
}

int _mainp()
{
    int nValue = 8;

    int* pnValue = &nValue;

    cout << "Int value: " << nValue << endl;
    cout << "Pointer to the value " << pnValue << endl;
    cout << "Int value using pointer " << *pnValue << endl;

    double dValue = 123.4;

    cout << "1. dvalue: " << dValue << endl;
    manipulate(dValue);
    cout << "4. dvalue: " << dValue << endl;

    return 0;
}