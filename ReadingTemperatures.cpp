//
// Created by panos on 30/06/18.
//

#include "../std_lib_facilities.h"

constexpr int implausible_min = -200;
constexpr int implausible_max = 200;
const double not_a_reading = -77777;
const int not_a_month = -1;
const int months = 12, days = 32, hours = 24;
const string month_prefix = "month", year_prefix = "year";
const map<string, int> month_names {
    {"jan", 0}, {"feb", 1}, {"mar", 2}, {"apr", 3}, {"may", 4}, {"jun", 5},
    {"jul", 6}, {"aug", 7}, {"sep", 8}, {"oct", 9}, {"nov", 10}, {"dec", 11}
};

const vector<string> month_print_tbl = {
    "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"
};

struct Day {
    vector<double> hour {vector<double>(hours, not_a_reading)};
};

struct Month {
    int month {not_a_month};
    vector<Day> day {vector<Day>(days)};
};

struct Year {
    int year;
    vector<Month> month {vector<Month>(months)};
};

struct Reading {
    int day;
    int hour;
    double temperature;
};

// Helper functions declaration

istream& clear_istream(istream &is);

void end_of_loop(istream& is, const char& term, const string& message);

int month_to_int(const string& mm);

bool is_valid(const Reading& r);

void print_year(ostream& os, const Year& y);

string int_to_month(int i);

/**
 * Read a temperature reading from is into r
 * format ( 3 4 9.7 )
 * check format, but don't bother with data validity
 *
 * @param is
 * @param r
 * @return is
 */
istream& operator>>(istream& is, Reading& r)
{
    char ch1;
    if (is>>ch1 && ch1!='(') {
        return clear_istream(is);
    }

    char ch2;
    int d;
    int h;
    double t;
    is >> d >> h >> t >> ch2;
    if (!is || ch2!=')') error("bad reading");
    r.day = d;
    r.hour = h;
    r.temperature = t;
    return is;
}

/**
 * Read a month from is into m
 * format: {month feb ...}
 *
 * @param is
 * @param m
 * @return is
 */
istream& operator>>(istream& is, Month& m)
{
   char ch1;
   if (is>>ch1 && ch1!='{') {
       return clear_istream(is);
   }

   string month_maker;
   string mm;
   is >> month_maker >> mm;
   if(!is || month_maker!=month_prefix) error("bad start of month");
   m.month = month_to_int(mm);
   int duplicates = 0;
   int invalids = 0;
   for (Reading r; is >> r;) {
       if (is_valid(r)) {
           if (m.day[r.day].hour[r.hour] != not_a_reading)
               ++duplicates;
           m.day[r.day].hour[r.hour]=r.temperature;
       }
       else
           ++invalids;
   }
   if (invalids) error("invalid reading in month", invalids);
   if (duplicates) error("duplicate readings in month", duplicates);
   end_of_loop(is, '}', "bad end of month");
   return is;
}

/**
 * Read a year from is into y
 * format: {year 2004 ...}
 *
 * @param is
 * @param y
 * @return is
 */
istream& operator>>(istream& is, Year& y)
{
    char ch;
    if (is >> ch && ch != '{') {
        return clear_istream(is);
    }

    string year_maker;
    int yy;
    is >> year_maker >> yy;
    if(!is || year_maker != year_prefix) error("bad start of year");
    y.year = yy;

    while(true) {
        Month m;
        if(!(is>>m)) break;
        y.month[m.month] = m;
    }

    end_of_loop(is, '}', "bad end of year");
    return is;
}

int mainreadingtemperature() {
    // open an input file:
    cout << "Please enter input file name\n";
    string iname;
    cin >> iname;
    ifstream ist{iname};
    if(!ist) error("can't open input file", iname);
    ist.exceptions(ist.exceptions()|ios_base::failbit); // throw for bad()

    // open an output file:
    cout << "Please enter output file name\n";
    string oname;
    cin >> oname;
    ofstream ost{oname};
    if (!ost) error("can't open file", oname);

    // read an arbitary number of years:
    vector<Year> ys;
    while(true) {
        Year y;
        if (!(ist>>y)) break;
        ys.push_back(y);
    }
    cout << "read" << ys.size() << " years of readings\n";
    for (Year& y : ys) print_year(ost, y);
}


// Helper functions implementation

istream& clear_istream(istream &is)
{
    is.unget();
    is.clear(ios_base::failbit);
    return is;
}

void end_of_loop(istream& is, const char& term, const string& message)
{
    if (is.fail()) {
        is.clear();
        char ch;
        if (is>>ch && ch==term) return;
        error(message);
    }
}

int month_to_int(const string& mm)
{
    return month_names.at(mm);
}

string int_to_month(int i)
{
    if (i < 0 || months <= i) error("bad month index");
    return month_print_tbl[i];
}

bool is_valid(const Reading& r)
{
    if (r.day < 1 || 31 < r.day) return false;
    if (r.hour < 0 || 23 < r.hour) return false;
    return !(r.temperature < implausible_min || implausible_max < r.temperature);
}

void print_day(ostream& os, const Day& d, const int& idx)
{
    for (unsigned int i = 0; i < d.hour.size(); i++)
        if (d.hour.at(i) != not_a_reading)
            os << "( " << idx << ' ' << i << ' ' << d.hour.at(i) << " ) ";
}

void print_month(ostream& os, const Month& m)
{
    if (m.month == not_a_month) return;
    os << "{month " << m.month << " ";
    for (unsigned int i = 0; i < m.day.size(); i++) print_day(os, m.day.at(i), i + 1);
    os << "}\n";
}

void print_year(ostream& os, const Year& y)
{
    os << "{year " << y.year << '\n';
    for (Month m : y.month) print_month(os, m);
    os << "}\n";
}