#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>
#include <stdio.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdexcept>
#include <math.h>
#include <iostream>
#include "timespan.h"

using namespace std;

enum weekday { sunday, monday, tuesday, wednesday, thursday, friday, saturday };

class __declspec(dllexport) datetime
{
    public:
        datetime();
        datetime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);
        datetime(const datetime&);
        const datetime& operator=(const datetime &dt);
        friend std::ostream& operator<<(std::ostream &os, const datetime &dt);
		__declspec(dllexport) friend bool operator<(const datetime &mdt, const datetime &odt);
		__declspec(dllexport) friend bool operator>(const datetime &mdt, const datetime &odt);
        __declspec(dllexport) friend bool operator<=(const datetime &mdt, const datetime &odt);
		__declspec(dllexport) friend bool operator>=(const datetime &mdt, const datetime &odt);
		__declspec(dllexport) friend timespan operator-(const datetime& mdt, const datetime &odt);
        virtual ~datetime();
        string to_string() const;
        string to_string(string format) const;
        string to_shortdate_string() const;
        int get_year() const;
        int get_month() const;
        int get_day() const;
        int get_hour() const;
        int get_minute() const;
        int get_second() const;
        weekday get_weekday() const;
        void add_years(int nb_years);
        void add_months(int nb_months);
        void add_days(int nb_days);
        void add_hours(int nb_hours);
        void add_minutes(int nb_minutes);
        void add_seconds(int nb_seconds);
        bool is_leapyear();
        static datetime parse(string format, string value);
    protected:
        const int ONE_DAY = 86400; //24 hours * 60 mins * 60 secs
        const int ONE_HOUR = 3600; //60 mins * 60 secs
        const int ONE_MINUTE = 60; // 60 secs
        struct tm *timeInfo = nullptr;
        bool auto_created = true;
        bool _is_leapyear(int year) const;
        static int _parse_intvalue(string pattern, int index, int mask_length, string parse_str);
        void _copy_from(const tm* otm);
};

#endif // DATETIME_H
