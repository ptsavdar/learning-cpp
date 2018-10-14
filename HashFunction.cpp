//
// Created by panos on 15/07/18.
//
#include <iostream>

using namespace std;

// djb2 hash function
unsigned long hashcode(const char *str)
{
    unsigned long hash = 5381; // prime(5381) = 709 (prime number), prime(709) = 127, ... prime(3) = 2
    int c;

    while (c = *str++)
    {
        hash = ((hash << 5 + hash)) + c; // hash * 33 + c
    }

    return hash;
}


int mainhashfunction()
{
    cout << "This is a test string: hash: " << hashcode("This is a test string") << endl;
    cout << "trex: hash: " << hashcode("trex") << endl;
    cout << "dinosaure: hash: " << hashcode("This is a test string") << endl;
    cout << "hash: " << hashcode("This is a test string") << endl;

    return 0;
}