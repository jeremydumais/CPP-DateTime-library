#include "include/datetime.h"

//Default constructor get current date and time
datetime::datetime()
{
    time_t now = time(0);
    tm* tm_now = localtime(&now);
    timeInfo = new tm();
    _copy_from(tm_now);
}

datetime::datetime(int year, int month, int day, int hour, int minute, int second)
{
    //Check out of range limit
    if (month < 1 || month > 12)
        throw invalid_argument("month must be between 1 and 12");
    if (day < 1)
        throw invalid_argument("day is out of range");
    if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 or month == 12) && day > 31)
        throw invalid_argument("day is out of range");
    else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        throw invalid_argument("day is out of range");
    else if (month == 2 && this->_is_leapyear(year) && day >29)
        throw invalid_argument("day is out of range");
    else if (month == 2 && !this->_is_leapyear(year) && day >28)
        throw invalid_argument("day is out of range");
    if (hour < 0 || hour > 23)
        throw invalid_argument("hour must be between 0 and 23");
    if (minute < 0 || minute > 59)
        throw invalid_argument("minute must be between 0 and 59");
    if (second < 0 || second > 59)
        throw invalid_argument("second must be between 0 and 59");
    timeInfo = new tm();
    timeInfo->tm_year = year - 1900;
    timeInfo->tm_mon = month - 1;
    timeInfo->tm_mday = day;
    timeInfo->tm_hour = hour;
    timeInfo->tm_min = minute;
    timeInfo->tm_sec = second;
    mktime(timeInfo);
}

datetime::datetime(const datetime &other)
{
    timeInfo = new tm();
    _copy_from(other.timeInfo);
}

const datetime& datetime::operator=(const datetime &dt)
{
    if (this != &dt)
        _copy_from(dt.timeInfo);
    return *this;
}

datetime::~datetime()
{
    delete timeInfo;
}

bool datetime::_is_leapyear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || ( year % 400 == 0))
        return true;
    else
        return false;
}

string datetime::to_string()
{
    char retVal[128] = "";
    sprintf(retVal, "%d-%02d-%02d %02d:%02d:%02d",
            get_year(),
            get_month(),
            get_day(),
            get_hour(),
            get_minute(),
            get_second() );
    return string(retVal);

}

string datetime::to_shortdate_string()
{
    char retVal[128] = "";
    sprintf(retVal, "%d-%02d-%02d",
            get_year(),
            get_month(),
            get_day());
    return string(retVal);
}

int datetime::get_year()
{
    return timeInfo->tm_year + 1900;
}

int datetime::get_month()
{
    return timeInfo->tm_mon+1;
}

int datetime::get_day()
{
    return timeInfo->tm_mday;
}

int datetime::get_hour()
{
    return timeInfo->tm_hour;
}

int datetime::get_minute()
{
    return timeInfo->tm_min;
}

int datetime::get_second()
{
    return timeInfo->tm_sec;
}

void datetime::add_years(int nb_years)
{
    timeInfo->tm_year += nb_years;
}

void datetime::add_months(int nb_months)
{
    //Get number of year
    int nb_year = ceil(nb_months / 12);
    int nb_months_final = nb_months % 12;

    if (timeInfo->tm_mon + nb_months_final > 11)  // tm_mon is from 0 to 11
    {
        nb_year++;
        nb_months_final =  (timeInfo->tm_mon + nb_months_final) - 12;
        timeInfo->tm_mon = nb_months_final;
    }
    else
        timeInfo->tm_mon += nb_months_final;

    timeInfo->tm_year += nb_year;
}

void datetime::add_days(int nb_days)
{
    add_seconds(nb_days * ONE_DAY);
}

void datetime::add_hours(int nb_hours)
{
    add_seconds(nb_hours * ONE_HOUR);
}

void datetime::add_minutes(int nb_minutes)
{
    add_seconds(nb_minutes * ONE_MINUTE);
}

void datetime::add_seconds(int nb_seconds)
{
    time_t new_seconds = mktime(timeInfo) + nb_seconds;
    delete timeInfo;
    tm* tm_new_time = localtime(&new_seconds);
    timeInfo = new tm();
    _copy_from(tm_new_time);
}

bool datetime::is_leapyear()
{
    return _is_leapyear(get_year());
}

void datetime::_copy_from(const tm * otm)
{
    timeInfo->tm_year = otm->tm_year;
    timeInfo->tm_mon = otm->tm_mon;
    timeInfo->tm_mday = otm->tm_mday;
    timeInfo->tm_hour = otm->tm_hour;
    timeInfo->tm_min = otm->tm_min;
    timeInfo->tm_sec = otm->tm_sec;
    timeInfo->tm_isdst = otm->tm_isdst;
    timeInfo->tm_wday = otm->tm_wday;
    timeInfo->tm_yday = otm->tm_yday;
}

// Operators
std::ostream& operator<<(std::ostream& os, const datetime& dt)
{
    char retVal[128] = "";
    sprintf(retVal, "%d-%02d-%02d %02d:%02d:%02d",
            dt.timeInfo->tm_year + 1900,
            dt.timeInfo->tm_mon + 1,
            dt.timeInfo->tm_mday,
            dt.timeInfo->tm_hour,
            dt.timeInfo->tm_min,
            dt.timeInfo->tm_sec);
    os << retVal;

    return os;
}

bool operator<(const datetime& mdt, const datetime& odt)
{
    return mktime(mdt.timeInfo) < mktime(odt.timeInfo);
}

bool operator>(const datetime& mdt, const datetime& odt)
{
    return mktime(odt.timeInfo) < mktime(mdt.timeInfo);
}

bool operator<=(const datetime& mdt, const datetime& odt)
{
    return !(mktime(mdt.timeInfo) > mktime(odt.timeInfo));
}

bool operator>=(const datetime& mdt, const datetime& odt)
{
    return !(mktime(mdt.timeInfo) < mktime(odt.timeInfo));
}
