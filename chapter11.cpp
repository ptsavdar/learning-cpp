//
// Created by panos on 02/07/18.
//

#include "../std_lib_facilities.h"

int mainchapter11()
{
    double t = 123459.123;
    int i = 123456;

    cout << defaultfloat << setprecision(11) << t << '\t' << fixed << t << '\t' << scientific << t << endl;
    cout << i << '|' << setw(4) << i << '|' << setw(8) << i << '|' << i << '\n';
}