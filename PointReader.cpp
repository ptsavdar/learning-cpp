//
// Created by panos on 30/06/18.
//

#include "../std_lib_facilities.h"

struct Point {
    double x;
    double y;
};


// Helper functions declaration

istream& clear_is(istream &is);

void eol(istream& is, const char& term, const string& message);

ostream& operator<<(ostream& os, const Point& p)
{
    os << '(' << p.x << ", " << p.y << ')' << endl;
    return os;
}

/**
 * Reading point p from is
 * format: (x, y)
 *
 * @param is
 * @param p
 * @return is
 */
istream& operator>>(istream& is, Point& p)
{
    if (is.eof()) return is;
    char ch;
    if (is>>ch && ch != '(')
        return clear_is(is);
    double x;
    char ch2;
    double y;
    char ch3;
    is >> x >> ch2 >> y >> ch3;
    if (!is) return is;
    if (ch2 != ',') error("bad point format ", ch2);
    p.x = x;
    p.y = y;
    eol(is, ')', "bad ending point");
    return is;
}

int mainpointreader()
{
    cout << "Please enter 7 original_points\n";
    vector<Point> original_points;
    for (int i = 0; i < 3; i++)
    {
        cout << "Please enter point no " << i + 1 << endl;
        Point p;
        cin >> p;
        original_points.push_back(p);
    }

    cout << "You entered the following points: " << endl;
    for (Point p : original_points)
        cout << p;

    ofstream ost{"mydata.txt"};
    if (!ost) error("cannot open file for writing");

    cout << "Original points: " << '\n';
    for (Point p : original_points)
        ost << p;

    ifstream ist{"mydata.txt"};
    if (!ist) error("cannot open file for reading");
    //ist.exceptions(ist.exceptions() | ios_base::failbit);

    vector<Point> processed_points;
    for(Point p; ist>>p;) processed_points.push_back(p);

    cout << "Processed points: " << '\n';
    for (Point p : processed_points)
        cout << p;

    return 0;
}

// Helper functions implementation

istream& clear_is(istream &is)
{
    is.unget();
    is.clear(ios_base::failbit);
    return is;
}

void eol(istream& is, const char& term, const string& message)
{
    if (is.fail()) {
        is.clear();
        char ch;
        if (is>>ch && ch==term) return;
        error(message);
    }
}