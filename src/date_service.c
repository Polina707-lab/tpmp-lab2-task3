#include "date_service.h"

int date_is_leap_year(int year) {
    if (year % 400 == 0) return 1;
    if (year % 100 == 0) return 0;
    return (year % 4 == 0);
}

int date_days_in_month(int year, int month) {
    static const int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (month < 1 || month > 12) return 0;
    if (month == 2) return days[1] + (date_is_leap_year(year) ? 1 : 0);
    return days[month - 1];
}

int date_is_valid(Date d) {
    if (d.year < 1 || d.year > 9999) return 0;
    if (d.month < 1 || d.month > 12) return 0;
    int dim = date_days_in_month(d.year, d.month);
    if (d.day < 1 || d.day > dim) return 0;
    return 1;
}

Date date_prev_day(Date d) {
    d.day--;
    if (d.day >= 1) return d;
    d.month--;
    if (d.month >= 1) {
        d.day = date_days_in_month(d.year, d.month);
        return d;
    }

    d.year--;
    d.month = 12;
    d.day = 31;
    return d;
}

Date date_next_day(Date d) {
    d.day++;
    int dim = date_days_in_month(d.year, d.month);
    if (d.day <= dim) return d;

    d.day = 1;
    d.month++;
    if (d.month <= 12) return d;

    d.month = 1;
    d.year++;
    return d;
}

static int to_ordinal(Date d) {
    // Converts date to "day count" since 0001-01-01 (simple, for differences)
    // Works for valid dates.
    int y = d.year;
    int m = d.month;
    int total = 0;

    // days for complete years before y
    int y1 = y - 1;
    total += y1 * 365;
    total += y1 / 4 - y1 / 100 + y1 / 400;

    // days for complete months before m in year y
    for (int mm = 1; mm < m; mm++) {
        total += date_days_in_month(y, mm);
    }
    total += d.day - 1;
    return total;
}

int date_days_between(Date a, Date b) {
    // b - a
    if (!date_is_valid(a) || !date_is_valid(b)) return 0;
    return to_ordinal(b) - to_ordinal(a);
}
