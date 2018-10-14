//
// Created by panos on 27/05/18.
//

#include "../std_lib_facilities.h";

int ex310() {
    cout << "Enter operation and operands: " << endl;
    string operation;
    double val1 = 0, val2 = 0;
    cin >> operation >> val1 >> val2;
    double res = 0;
    bool accept = true;
    if (operation == "+") res = val1 + val2;
    else if (operation == "-") res = val1 - val2;
    else if (operation == "*") res = val1 * val2;
    else if (operation == "/") res = val1 / val2;
    else accept = false;
    if (accept) cout << "Result: " << res << endl;
    else cout << "Not recognised operation" << endl;

    return 0;
}

