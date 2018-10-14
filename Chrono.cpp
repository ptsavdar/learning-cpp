//
// Created by panos on 23/06/18.
//

#include "Chrono.h"

namespace Chrono {
    // member function definitions

    Date::Date(int yy, Month mm, int dd) : y{yy}, m{mm}, d{dd}
    {
        if (!is_date(*this)) throw Invalid{};
    }

    const Date& default_date()
    {
        static Date dd {2001, Month::jan, 1}; // start of 21st century
        return dd;
    }

    Date::Date() : y{default_date().year()}, m{default_date().month()}, d{default_date().day()} {}

    void Date::add_day(int n)
    {
        if (n == 0) return;

        d += n;
        int dim = days_in_month(*this);

        while (dim < d) {
            d -= dim;
            this->add_month(1);
            dim = days_in_month(*this);
        }
    }

    void Date::add_month(int n)
    {
        if (n == 0) return;

        int month = static_cast<int>(m) + n;
        int years{0};
        while (static_cast<int>(Month::dec) < month) {
            month -= static_cast<int>(Month::dec);
            years++;
        }
        m = Month(month);
        this->add_year(years);
    }

    void Date::add_year(int n)
    {
        if (n == 0) return;

        if (m == Month::feb && d == 29 && !leapyear(y + n)) {     // beware of leap years!
            m = Month::mar;                                     // use March 1 instead of February 29
            d = 1;
        }

        y += n;
    }

    // helper functions:
    int days_in_month(const Date& d)
    {
        int days_in_month = 31;

        switch (d.month()) {
            case Month::feb:
                days_in_month = (leapyear(d.year())) ? 29 : 28;
                break;
            case Month::apr: case Month::jun: case Month::sep: case Month::nov:
                days_in_month = 30;
                break;
        }

        return days_in_month;
    }

    bool is_date(const Date& d)
    {
        if (d.day() <= 0) return false;       // day must be positive
        if (d.month() < Month::jan || Month::dec < d.month()) return false;

        int dim = days_in_month(d);

        return d.day() <= dim;
    }

    bool leapyear(int y)
    {
        return y % 4 == 0 && (y % 100 != 0 || (y % 100 == 0 && y % 400 == 0));
    }

    bool operator==(const Date& a, const Date& b)
    {
        return a.year() == b.year() && a.month() == b.month() && a.day() == b.day();
    }

    bool operator!=(const Date& a, const Date& b)
    {
        return !(a==b);
    }

    ostream& operator<<(ostream& os, const Day& d)
    {
        return os << static_cast<underlying_type<Day>::type>(d);
    }

    ostream& operator<<(ostream& os, const Month& m)
    {
        return os << static_cast<underlying_type<Month>::type>(m);
    }

    ostream& operator<<(ostream& os, const Date& d)
    {
        return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
    }

    istream& operator>>(istream& is, Date& dd)
    {
        int y, m, d;
        char ch1, ch2, ch3, ch4;
        is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
        if (!is) return is;
        if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')')
        {
            is.clear(ios_base::failbit);
            return is;
        }

        dd = Date(y, Month(m), d);

        return is;
    }

    Day day_of_week(const Date& d)
    {
        // zeller's rule
        int m = static_cast<int>(d.month()) - 2 + ((static_cast<int>(d.month()) < 3) ? 12 : 0);
        int y = m > 10 ? d.year() - 1 : d.year();
        int C = y / 100;
        int D = y - (C * 100);
        // cout << m << ", " << y << ", " << C << ", " << D << endl;
        int f = d.day() + (13 * m - 1)/5 + D + D/4 + C/4 - 2 * C + 7;

        return Day(f % 7);
    }

    int day_of_year(const Date& d)
    {
        int n1 = (275 * static_cast<int>(d.month())) / 9;
        int n2 = (static_cast<int>(d.month()) + 9) / 12;
        int n3 = leapyear(d.year()) ? 1 : 2;

        return n1 - n2 * n3 + d.day() - 30;
    }

    Date next_sunday(const Date& d)
    {
        Day dow = day_of_week(d);
        Date ns = d;
        ns.add_day(7 - static_cast<int>(dow));

        return ns;
    }

    Date next_week(const Date& d)
    {
        Date nw = d;
        nw.add_day(7);

        return nw;
    }
}