//
// Created by panos on 27/05/18.
//

#include <iostream>;
using namespace std;

int drill4() {
    //int sv = INT32_MAX, lv = INT32_MIN;
    double v1, v2;
    while (cin >> v1 >> v2) {
        if (v1 == v2) cout << "The numbers are equal" << endl;
        else if (abs(v1 - v2) <= 1.0/100) cout << "The numbers are almost equal" << endl;
        else {
            cout << "The smaller value is: " << min(v1, v2) << endl;
            cout << "The larger value is: " << max(v1, v2) << endl;
        }

    }
}
