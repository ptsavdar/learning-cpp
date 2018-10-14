//
// Created by panos on 23/06/18.
//

#include "../std_lib_facilities.h"
#include "Chrono.h"

using namespace Chrono;

int mainchrono() {
    Date today{1900, Month(2), 25};
    Date tomorrow = today;
    tomorrow.add_day(309);

    cout << today << endl;
    cout << tomorrow << endl;

    cout << day_of_week(today) << endl;
    cout << day_of_week(tomorrow) << endl;
    cout << day_of_week(next_sunday(today)) << endl;
    cout << day_of_week(next_sunday(tomorrow)) << endl;
    cout << day_of_year(today) << endl;
    cout << day_of_year(tomorrow) << endl;
    tomorrow.add_day(1);
    cout << tomorrow << endl;
    cout << day_of_week(tomorrow) << endl;

    return 0;
}