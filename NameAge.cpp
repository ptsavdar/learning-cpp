//
// Created by panos on 18/06/18.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<double> readAges(const vector<string>& names)
{
    vector<double> ages;
    for (const string &name : names)
    {
        cout << "Insert age for: " << name << " " << endl;
        double age;
        cin >> age;
        ages.push_back(age);
    }

    return ages;
}

void printPairs(const vector<string>& names, const vector<double>& ages)
{
    for (unsigned int i = 0;  i < names.size(); i++)
        cout << names.at(i) << " is " << ages.at(i) << " years old" << endl;
}

vector<double> sortAges(const vector<string> &names, const vector<string> &sortedNames, const vector<double> &ages)
{
    vector<double> sortedAges;
    for (const auto &sortedName : sortedNames) {
        for (unsigned int j = 0; j < names.size(); j++) {
            if (sortedName == names.at(j)) {
                sortedAges.push_back(ages.at(j));
                continue;
            }
        }
    }

    return sortedAges;
}

int mainnameage() {
    vector<string> names{"George", "Anna", "John", "Cercei", "Aria"};
    vector<string> sortedNames = names;
    vector<double> ages = readAges(names);
    printPairs(names, ages);
    cout << endl;
    sort(sortedNames.begin(), sortedNames.end());
    vector<double> sortedAges = sortAges(names, sortedNames, ages);
    printPairs(sortedNames, sortedAges);
    return 0;
}
