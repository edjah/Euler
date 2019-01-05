#include "lib/utility.h"

int days_per_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main(void) {
    start_time();

    // Jan 1, 1901 was a Tuesday
    int year = 1901;
    int month = 1;
    int day = 1;
    int weekday = 2;

    int answer = 0;
    while (year != 2000 || month != 12 || day != 31) {
        if (weekday == 7 && day == 1) {
            answer += 1;
        }

        bool leap_year = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
        if (month == 2 && leap_year) {
            day = 1 + day % 29;
        } else {
            day = 1 + day % days_per_month[month];
        }

        if (day == 1) {
            month = 1 + month % 12;
            if (month == 1) {
                year += 1;
            }
        }
        weekday = 1 + weekday % 7;
    }
    printf("Solution: %d\n", answer);

    end_time();
}
