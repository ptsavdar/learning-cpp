//
// Created by panos on 23/06/18.
//

#ifndef CPP_BEGINNERS_CHRONO_H
#define CPP_BEGINNERS_CHRONO_H

#include <iostream>
using namespace std;

namespace Chrono {

    enum class Month {
        jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
    };

    enum class Day {
        sunday, monday, tuesday, wednesday, thursday, friday, saturday
    };

    class Date {
    public:
        class Invalid {};               // to throw as exception

        Date(int y, Month m, int d);    // check for valid date and initialize
        Date();                         // default constructor
        // the default copy operations are fine

        // non modifying operations:
        int day() const { return d; }
        Month month() const { return m; }
        int year() const { return y; }

        // modifying operations:
        void add_day(int n);
        void add_month(int n);
        void add_year(int n);

    private:
        int y;
        Month m;
        int d;
    };

    bool is_date(const Date& d);            // true for valid date
    int days_in_month(const Date& d);       // returns number of days in month
    bool leapyear(int y);                   // true if y is leap year

    bool operator==(const Date& a, const Date& b);
    bool operator!=(const Date& a, const Date& b);

    ostream& operator<<(ostream& os, const Month& m);
    ostream& operator<<(ostream& os, const Day& d);
    ostream& operator<<(ostream& os, const Date& d);
    istream& operator>>(istream& is, Date& dd);

    Day day_of_week(const Date& d);
    Date next_sunday(const Date& d);
    Date next_week(const Date& d);
    int day_of_year(const Date& d);
};


#endif //CPP_BEGINNERS_CHRONO_H
