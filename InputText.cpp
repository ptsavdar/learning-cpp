//
// Created by panos on 27/05/18.
//

#include "../std_lib_facilities.h"

int input() {
    cout << "Enter your first name (followed by 'enter'): " << endl;
    string first_name;
    double age = -1;
    cin >> first_name;
    cin >> age;
    cout << "Hello, " << first_name << " age (" << age * 12 << ")" << endl;
}
