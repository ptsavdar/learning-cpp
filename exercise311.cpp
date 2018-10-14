//
// Created by panos on 27/05/18.
//

#include "../std_lib_facilities.h"

int ex311() {
    int pennies = 0, nickels = 0, dimes = 0, quarters = 0, half = 0;
    cout << "How many pennies do you hame?" << endl;
    cin >> pennies;
    cout << "How many nickels do you hame?" << endl;
    cin >> nickels;
    cout << "How many dimes do you hame?" << endl;
    cin >> dimes;
    cout << "How many quarters do you hame?" << endl;
    cin >> quarters;
    cout << "How many half-dollars do you hame?" << endl;
    cin >> half;
    cout << "You have " << pennies << " penn" << (pennies == 1 ? "y" : "ies") << endl;
    cout << "You have " << nickels << " nickel" << (nickels == 1 ? "" : "s") << endl;
    cout << "You have " << dimes << " dime" << (dimes == 1 ? "" : "s") << endl;
    cout << "You have " << quarters << " quarter" << (quarters == 1 ? "" : "s") << endl;
    cout << "You have " << half << " half-dollar" << (half == 1 ? "" : "s") << endl;
    double val = half * 0.5 + quarters * 0.25 + dimes * 0.1 + nickels * 0.05 + pennies * 0.01;
    cout << "The value of all your coins is $" << val;
}
