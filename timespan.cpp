#include "include\timespan.h"
#include <stdexcept>


timespan::timespan(int days, int hours, int minutes, int seconds)
	//days(days), hours(hours), minutes(minutes), seconds(seconds)
{
	//Check if the values submitted is valid
	if (hours < -23 || hours > 23)
		throw std::invalid_argument("hours must be between 0 and 23");
	if (minutes < -59 || minutes > 59)
		throw std::invalid_argument("minutes must be between 0 and 59");
	if (seconds < -59 || seconds > 59)
		throw std::invalid_argument("seconds must be between 0 and 59");
	this->days = days;
	this->hours = hours;
	this->minutes = minutes;
	this->seconds = seconds;
}

int timespan::get_days() const
{
	return days;
}

int timespan::get_hours() const
{
	return hours;
}

int timespan::get_minutes() const
{
	return minutes;
}

int timespan::get_seconds() const
{
	return seconds;
}

int timespan::get_total_hours() const
{
	return  (days * 24) + hours;
}

int timespan::get_total_minutes() const
{
	return  (days * 60 * 24) + (hours * 60) + minutes;
}

int timespan::get_total_seconds() const
{
	return  (days * 60 * 60 * 24) + (hours * 60 * 60) + (minutes * 60) + seconds;
}