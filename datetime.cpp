#include "include/datetime.h"

//Default constructor get current date and time
datetime::datetime()
{
    time_t now = time(0);
    this->timeInfo = localtime(&now);
    this->auto_created = true;
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
    this->timeInfo = new tm();
    this->timeInfo->tm_year = year - 1900;
    this->timeInfo->tm_mon = month - 1;
    this->timeInfo->tm_mday = day;
    this->timeInfo->tm_hour = hour;
    this->timeInfo->tm_min = minute;
    this->timeInfo->tm_sec = second;
    this->auto_created = false;
}

datetime::datetime(const datetime &other)
{
    this->auto_created = other.auto_created;
    this->timeInfo = new tm();
    this->timeInfo->tm_year = other.timeInfo->tm_year;
    this->timeInfo->tm_mon = other.timeInfo->tm_mon;
    this->timeInfo->tm_mday = other.timeInfo->tm_mday;
    this->timeInfo->tm_hour = other.timeInfo->tm_hour;
    this->timeInfo->tm_min = other.timeInfo->tm_min;
    this->timeInfo->tm_sec = other.timeInfo->tm_sec;
}

const datetime& datetime::operator=(const datetime &)
{
    return *this;
}

datetime::~datetime()
{
    if (!this->auto_created)
        delete this->timeInfo;
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
    sprintf(retVal, "%d-%02d-%02d %02d:%02d:%02d", this->get_year(), this->get_month(), this->get_day(), this->get_hour(), this->get_minute(), this->get_second() );
    return string(retVal);

}

string datetime::to_shortdate_string()
{
    char retVal[128] = "";
    sprintf(retVal, "%d-%02d-%02d", this->get_year(), this->get_month(), this->get_day());
    return string(retVal);
}

int datetime::get_year()
{
    return this->timeInfo->tm_year + 1900;
}

int datetime::get_month()
{
    return this->timeInfo->tm_mon+1;
}

int datetime::get_day()
{
    return this->timeInfo->tm_mday;
}

int datetime::get_hour()
{
    return this->timeInfo->tm_hour;
}

int datetime::get_minute()
{
    return this->timeInfo->tm_min;
}

int datetime::get_second()
{
    return this->timeInfo->tm_sec;
}

void datetime::add_years(int nb_years)
{
    this->timeInfo->tm_year += nb_years;
}

void datetime::add_months(int nb_months)
{
    //Get number of year
    int nb_year = ceil(nb_months / 12);
    int nb_months_final = nb_months % 12;

    if (this->timeInfo->tm_mon + nb_months_final > 11)  // tm_mon is from 0 to 11
    {
        nb_year++;
        nb_months_final =  (this->timeInfo->tm_mon + nb_months_final) - 12;
        this->timeInfo->tm_mon = nb_months_final;
    }
    else
        this->timeInfo->tm_mon += nb_months_final;

    this->timeInfo->tm_year += nb_year;
}

void datetime::add_days(int nb_days)
{
    this->add_seconds(nb_days * ONE_DAY);
}

void datetime::add_seconds(int nb_seconds)
{
    time_t new_seconds = mktime(this->timeInfo) + nb_seconds;
    if (!this->auto_created)
        delete this->timeInfo;
    this->timeInfo = localtime(&new_seconds);
    this->auto_created = true;
}

bool datetime::is_leapyear()
{
    return this->_is_leapyear(this->get_year());
}

