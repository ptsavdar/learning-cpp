//
// Created by panos on 19/06/18.
//

#include <iostream>
using namespace std;


double birthday(const int &n)
{
    double days = 365;
    double prob = 1;

    for (int i = 1; i < n; i++) {
        prob *= (days - i) / days;
    }

    return prob;
}

double sampleReplacement(const int &n)
{
    double prob = 1;

    for (int i = 0; i < n; ++i)
    {
        prob *= (double)(n - 1) / (double)n;
    }

    return prob;
}

int mainbirthdayproblem()
{

    /*for (int i = 1; i < 51; i++) {
        cout << i << ": " << birthday(i) << endl;
    }*/

    for (int i = 1; i < 10000; i++) {
        cout << i << ": " << sampleReplacement(i) << endl;
    }

    return 0;
}