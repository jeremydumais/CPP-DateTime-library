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

namespace jed_utils
{
	enum weekday { sunday, monday, tuesday, wednesday, thursday, friday, saturday };

	class __declspec(dllexport) datetime
	{
	public:
		datetime();
		datetime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);
		datetime(const datetime&);
		const datetime& operator=(const datetime &dt);
		virtual ~datetime();
		friend std::ostream& operator<<(std::ostream &os, const datetime &dt);
		__declspec(dllexport) friend bool operator<(const datetime &mdt, const datetime &odt);
		__declspec(dllexport) friend bool operator>(const datetime &mdt, const datetime &odt);
		__declspec(dllexport) friend bool operator<=(const datetime &mdt, const datetime &odt);
		__declspec(dllexport) friend bool operator>=(const datetime &mdt, const datetime &odt);
		__declspec(dllexport) friend bool operator==(const datetime& mdt, const datetime &odt);
		__declspec(dllexport) friend bool operator!=(const datetime& mdt, const datetime &odt);
		__declspec(dllexport) friend timespan operator-(const datetime& mdt, const datetime &odt);
		std::string to_string() const;
		std::string to_string(std::string format) const;
		std::string to_shortdate_string() const;
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
		static datetime parse(std::string format, std::string value);
	protected:
		const int ONE_DAY = 86400; //24 hours * 60 mins * 60 secs
		const int ONE_HOUR = 3600; //60 mins * 60 secs
		const int ONE_MINUTE = 60; // 60 secs
		struct tm *timeInfo = nullptr;
		bool auto_created = true;
		bool _is_leapyear(int year) const;
		static int _parse_intvalue(std::string pattern, int index, int mask_length, std::string parse_str);
		void _copy_from(const tm* otm);
	};
}

#endif // DATETIME_H
