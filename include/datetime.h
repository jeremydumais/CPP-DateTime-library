#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <stdexcept>
#include <math.h>
#include <iostream>

using namespace std;

class datetime
{
    public:
        datetime();
        datetime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);
        datetime(const datetime&);
        const datetime& operator=(const datetime& dt);
        friend std::ostream& operator<<(std::ostream& os, const datetime& dt);
        friend bool operator<(const datetime& mdt, const datetime& odt);
        friend bool operator>(const datetime& mdt, const datetime& odt);
        friend bool operator<=(const datetime& mdt, const datetime& odt);
        friend bool operator>=(const datetime& mdt, const datetime& odt);
        virtual ~datetime();
        string to_string();
        string to_shortdate_string();
        int get_year();
        int get_month();
        int get_day();
        int get_hour();
        int get_minute();
        int get_second();
        void add_years(int nb_years);
        void add_months(int nb_months);
        void add_days(int nb_days);
        void add_hours(int nb_hours);
        void add_minutes(int nb_minutes);
        void add_seconds(int nb_seconds);
        bool is_leapyear();
    protected:
        const time_t ONE_DAY = 86400; //24 hours * 60 mins * 60 secs
        const time_t ONE_HOUR = 3600; //60 mins * 60 secs
        const time_t ONE_MINUTE = 60; // 60 secs
        struct tm *timeInfo = nullptr;
        bool auto_created = true;
        bool _is_leapyear(int year);
        void _copy_from(const tm* otm);
};

#endif // DATETIME_H
