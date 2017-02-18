// datetime_unittest.cpp : définit le point d'entrée pour l'application console.
//
#include "..\..\include\datetime.h"
#include <iostream>
#include <assert.h>
#include <cstring>
#include <exception>

using namespace std;
using namespace jed_utils;

void test_constructor()
{
	datetime dtTest(2015, 02, 14);
	assert(dtTest.get_year() == 2015);
	assert(dtTest.get_month() == 2);
	assert(dtTest.get_day() == 14);
	assert(dtTest.get_hour() == 0);
	assert(dtTest.get_minute() == 0);
	assert(dtTest.get_second() == 0);

	dtTest = datetime(2015, 02, 14, 23, 12, 11);
	assert(dtTest.get_year() == 2015);
	assert(dtTest.get_month() == 2);
	assert(dtTest.get_day() == 14);
	assert(dtTest.get_hour() == 23);
	assert(dtTest.get_minute() == 12);
	assert(dtTest.get_second() == 11);

	// Invalid month (under)
	try { datetime dtTestExept(2015, 00, 14); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "month must be between 1 and 12") == 0);
	}
	// Invalid month (over)
	try { datetime dtTestExept(2015, 13, 14); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "month must be between 1 and 12") == 0);
	}
	// Invalid day (under)
	try { datetime dtTestExept(2015, 1, 0); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "day is out of range") == 0);
	}
	// Invalid day (over)
	int month_to_check_31[] = { 1,3,5,7,8,10,12 };
	for (int i : month_to_check_31)
	{
		try { datetime dtTestExept(2015, i, 32); }
		catch (const std::invalid_argument &e) {
			assert(strcmp(e.what(), "day is out of range") == 0);
		}
	}

	int month_to_check_30[] = { 4,6,9,11 };
	for (int i : month_to_check_30)
	{
		try { datetime dtTestExept(2015, i, 31); }
		catch (const std::invalid_argument &e) {
			assert(strcmp(e.what(), "day is out of range") == 0);
		}
	}

	try { datetime dtTestExept(2000, 2, 30); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "day is out of range") == 0);
	}
	dtTest = datetime(2000, 02, 29);

	try { datetime dtTestExept(2001, 2, 29); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "day is out of range") == 0);
	}
	dtTest = datetime(2001, 02, 28);

	// Invalid hour (under)
	try { datetime dtTestExept(2015, 1, 14, -1); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "hour must be between 0 and 23") == 0);
	}
	// Invalid hour (over)
	try { datetime dtTestExept(2015, 1, 14, 24); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "hour must be between 0 and 23") == 0);
	}
	// Invalid minute (under)
	try { datetime dtTestExept(2015, 1, 14, 1, -1); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "minute must be between 0 and 59") == 0);
	}
	// Invalid minute (over)
	try { datetime dtTestExept(2015, 1, 14, 1, 60); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "minute must be between 0 and 59") == 0);
	}
	// Invalid second (under)
	try { datetime dtTestExept(2015, 1, 14, 1, 1, -1); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "second must be between 0 and 59") == 0);
	}
	// Invalid second (over)
	try { datetime dtTestExept(2015, 1, 14, 1, 1, 60); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "second must be between 0 and 59") == 0);
	}
}

void test_to_string()
{
	datetime dtTest = datetime(2015, 02, 14);
	assert(strcmp(dtTest.to_string().c_str(), "2015-02-14 00:00:00") == 0);

	dtTest = datetime(2015, 02, 14, 11, 7, 2);
	assert(strcmp(dtTest.to_string().c_str(), "2015-02-14 11:07:02") == 0);

	dtTest = datetime(2015, 02, 14, 11, 55, 45);
	assert(strcmp(dtTest.to_string().c_str(), "2015-02-14 11:55:45") == 0);
}

void test_to_shortdate_string()
{
	datetime dtTest = datetime(2015, 02, 14);
	assert(strcmp(dtTest.to_shortdate_string().c_str(), "2015-02-14") == 0);

	dtTest = datetime(2015, 02, 14, 11, 7, 2);
	assert(strcmp(dtTest.to_shortdate_string().c_str(), "2015-02-14") == 0);

	dtTest = datetime(2015, 02, 14, 11, 55, 45);
	assert(strcmp(dtTest.to_shortdate_string().c_str(), "2015-02-14") == 0);
}

void test_add_days()
{
	datetime dtTest = datetime(2015, 02, 14);
	dtTest.add_days(2);

	assert(strcmp(dtTest.to_shortdate_string().c_str(), "2015-02-16") == 0);

	dtTest = datetime(2015, 02, 27, 11, 7, 2);
	dtTest.add_days(5);
	assert(strcmp(dtTest.to_shortdate_string().c_str(), "2015-03-04") == 0);

	dtTest = datetime(2015, 02, 02, 11, 7, 2);
	dtTest.add_days(-3);
	assert(strcmp(dtTest.to_shortdate_string().c_str(), "2015-01-30") == 0);
}

void test_add_months()
{
	datetime dtTest = datetime(2015, 02, 14);
	dtTest.add_months(2);
	assert(strcmp(dtTest.to_shortdate_string().c_str(), "2015-04-14") == 0);

	dtTest = datetime(2015, 04, 14);
	dtTest.add_months(-2);
	assert(strcmp(dtTest.to_shortdate_string().c_str(), "2015-02-14") == 0);

	dtTest = datetime(2015, 11, 14);
	dtTest.add_months(3);
	assert(strcmp(dtTest.to_shortdate_string().c_str(), "2016-02-14") == 0);

	dtTest = datetime(2015, 11, 14);
	dtTest.add_months(23);
	assert(strcmp(dtTest.to_shortdate_string().c_str(), "2017-10-14") == 0);

	dtTest = datetime(2015, 11, 14);
	dtTest.add_months(-13);
	assert(strcmp(dtTest.to_shortdate_string().c_str(), "2014-10-14") == 0);
}

void test_add_years()
{
	datetime dtTest = datetime(2015, 02, 14);
	dtTest.add_years(2);
	assert(strcmp(dtTest.to_shortdate_string().c_str(), "2017-02-14") == 0);

	dtTest = datetime(2015, 02, 14);
	dtTest.add_years(-2);
	assert(strcmp(dtTest.to_shortdate_string().c_str(), "2013-02-14") == 0);
}

void test_is_leapyear()
{
	datetime dtTest(2000, 01, 01);
	assert(dtTest.is_leapyear());
	dtTest = datetime(2004, 01, 01);
	assert(dtTest.is_leapyear());
	dtTest = datetime(1700, 01, 01);
	assert(!dtTest.is_leapyear());
}

void test_add_hours()
{
	datetime dtTest = datetime(2015, 02, 14, 11);
	dtTest.add_hours(2);
	assert(strcmp(dtTest.to_string().c_str(), "2015-02-14 13:00:00") == 0);

	dtTest = datetime(2015, 02, 14, 23);
	dtTest.add_hours(2);
	assert(strcmp(dtTest.to_string().c_str(), "2015-02-15 01:00:00") == 0);

	dtTest = datetime(2015, 02, 14, 01);
	dtTest.add_hours(-48);
	assert(strcmp(dtTest.to_string().c_str(), "2015-02-12 01:00:00") == 0);
}

void test_add_minutes()
{
	datetime dtTest = datetime(2015, 02, 14, 11, 11);
	dtTest.add_minutes(30);
	assert(strcmp(dtTest.to_string().c_str(), "2015-02-14 11:41:00") == 0);

	dtTest = datetime(2015, 02, 14, 11, 00);
	dtTest.add_minutes(90);
	assert(strcmp(dtTest.to_string().c_str(), "2015-02-14 12:30:00") == 0);

	dtTest = datetime(2015, 02, 14, 00, 00);
	dtTest.add_minutes(-90);
	assert(strcmp(dtTest.to_string().c_str(), "2015-02-13 22:30:00") == 0);
}

void test_add_seconds()
{
	datetime dtTest = datetime(2015, 02, 14, 11, 11, 11);
	dtTest.add_seconds(30);
	assert(strcmp(dtTest.to_string().c_str(), "2015-02-14 11:11:41") == 0);

	dtTest = datetime(2015, 02, 14, 11, 11, 00);
	dtTest.add_seconds(90);
	assert(strcmp(dtTest.to_string().c_str(), "2015-02-14 11:12:30") == 0);

	dtTest = datetime(2015, 02, 14, 14, 00, 00);
	dtTest.add_seconds(-90);
	assert(strcmp(dtTest.to_string().c_str(), "2015-02-14 13:58:30") == 0);
}

void test_operator_less()
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 00);
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 01);
	assert(dtTest < dtTest2);

	dtTest = datetime(2015, 02, 14, 14, 00, 00);
	dtTest2 = datetime();
	assert(dtTest < dtTest2);

	dtTest = datetime(2015, 02, 14, 14, 00, 00);
	dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	assert(!(dtTest < dtTest2));
}

void test_operator_less_equal()
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 00);
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 01);
	assert(dtTest <= dtTest2);

	dtTest = datetime(2015, 02, 14, 14, 00, 00);
	dtTest2 = datetime();
	assert(dtTest <= dtTest2);

	dtTest = datetime(2015, 02, 14, 14, 00, 00);
	dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	assert(dtTest <= dtTest2);

	dtTest = datetime(2015, 02, 14, 14, 00, 01);
	dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	assert(!(dtTest <= dtTest2));
}

void test_operator_greater()
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 01);
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	assert(dtTest > dtTest2);

	dtTest = datetime();
	dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	assert(dtTest > dtTest2);

	dtTest = datetime(2015, 02, 14, 14, 00, 00);
	dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	assert(!(dtTest > dtTest2));
}

void test_operator_greater_equal()
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 01);
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	assert(dtTest >= dtTest2);

	dtTest = datetime();
	dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	assert(dtTest >= dtTest2);

	dtTest = datetime(2015, 02, 14, 14, 00, 00);
	dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	assert(dtTest >= dtTest2);

	dtTest = datetime(2015, 02, 14, 14, 00, 00);
	dtTest2 = datetime(2015, 02, 14, 14, 00, 01);
	assert(!(dtTest >= dtTest2));
}

void test_operator_equal()
{
	assert(datetime(2017, 1, 8, 15, 28, 23) == datetime(2017, 1, 8, 15, 28, 23));
	assert(datetime(2016, 12, 31, 23, 59, 59) == datetime(2016, 12, 31, 23, 59, 59));
}

void test_operator_not_equal()
{
	assert(!(datetime(2017, 1, 8, 15, 28, 23) != datetime(2017, 1, 8, 15, 28, 23)));
	assert(!(datetime(2016, 12, 31, 23, 59, 59) != datetime(2016, 12, 31, 23, 59, 59)));
	assert(datetime(2017, 1, 8, 15, 28, 23) != datetime(2017, 1, 8, 15, 28, 22));
	assert(datetime(2017, 1, 8, 15, 28, 23) != datetime(2017, 1, 8, 15, 27, 23));
	assert(datetime(2017, 1, 8, 15, 28, 23) != datetime(2017, 1, 8, 14, 28, 23));
	assert(datetime(2017, 1, 8, 15, 28, 23) != datetime(2017, 1, 7, 15, 28, 23));
	assert(datetime(2017, 1, 8, 15, 28, 23) != datetime(2017, 2, 8, 15, 28, 23));
	assert(datetime(2017, 1, 8, 15, 28, 23) != datetime(2016, 1, 8, 15, 28, 23));
}

void test_get_weekday()
{
	datetime dtTest = datetime(2015, 02, 14, 11, 11, 11);
	assert(dtTest.get_weekday() == weekday::saturday);

	dtTest = datetime(2015, 02, 15);
	assert(dtTest.get_weekday() == weekday::sunday);
}

void test_parse()
{
	datetime dtTest = datetime::parse(string("yyyy"), string("2016"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 1);
	assert(dtTest.get_day() == 1);

	dtTest = datetime::parse(string("yyyy-MM"), string("2016-04"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 4);
	assert(dtTest.get_day() == 1);

	dtTest = datetime::parse(string("yyyy/MM/dd"), string("2016-08-18"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 8);
	assert(dtTest.get_day() == 18);

	dtTest = datetime::parse(string("yyyy/MM/dd HH"), string("2016-08-18 23"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 8);
	assert(dtTest.get_day() == 18);
	assert(dtTest.get_hour() == 23);

	dtTest = datetime::parse(string("yyyy/MM/dd HH:mm"), string("2016-08-18 23:14"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 8);
	assert(dtTest.get_day() == 18);
	assert(dtTest.get_hour() == 23);
	assert(dtTest.get_minute() == 14);

	dtTest = datetime::parse(string("yyyy/MM/dd HH:mm:ss"), string("2016-08-18 23:14:42"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 8);
	assert(dtTest.get_day() == 18);
	assert(dtTest.get_hour() == 23);
	assert(dtTest.get_minute() == 14);
	assert(dtTest.get_second() == 42);

	dtTest = datetime::parse(string("yyyyMMddHHmmss"), string("20160818231442"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 8);
	assert(dtTest.get_day() == 18);
	assert(dtTest.get_hour() == 23);
	assert(dtTest.get_minute() == 14);
	assert(dtTest.get_second() == 42);

	try
	{
		dtTest = datetime::parse(string(""), string(""));
		assert(false);

	}
	catch (invalid_argument& err)
	{
		assert(strcmp(err.what(), "format") == 0);
	}
	catch (...) { assert(false); }

	try
	{
		dtTest = datetime::parse(string("yyyy"), string("allo"));
		assert(false);
	}
	catch (runtime_error& err)
	{
		assert(strcmp(err.what(), "Unable to parse the mask yyyy") == 0);
	}
	catch (...) { assert(false); }
}

void test_tostring_format()
{
	try
	{
		datetime dtTest = datetime();
		dtTest.to_string("");
		assert(false);
	}
	catch (invalid_argument& err)
	{
		assert(strcmp(err.what(), "format") == 0);
	}
	catch (...) { assert(false); }

	datetime dtTest = datetime(2015, 10, 14, 15, 12, 13);
	assert(dtTest.to_string("/02-yyyy/MM-dd") == "/02-2015/10-14");
	assert(dtTest.to_string("yyyy-MM-dd") == "2015-10-14");
	assert(dtTest.to_string("yyyy-M-d") == "2015-10-14");
	assert(dtTest.to_string("yyyy MM dd") == "2015 10 14");
	assert(dtTest.to_string("dd/MM/yyyy") == "14/10/2015");
	assert(dtTest.to_string("yyyy") == "2015");
	assert(dtTest.to_string("MM") == "10");
	assert(dtTest.to_string("dd") == "14");
	assert(dtTest.to_string("yyyy-MM-dd HH:mm:ss") == "2015-10-14 15:12:13");
	assert(dtTest.to_string("yyyy-MM-dd hh:mm:ss tt") == "2015-10-14 03:12:13 PM");
	assert(dtTest.to_string("yyyy-MM-dd h:mm:ss tt") == "2015-10-14 3:12:13 PM");
	assert(dtTest.to_string("yyyy-MM-dd H:m:s") == "2015-10-14 15:12:13");
	assert(dtTest.to_string("HH:mm:ss") == "15:12:13");
	assert(dtTest.to_string("aaaa") == ""); //Invalid format
	assert(dtTest.to_string("aaaa-ii") == "-"); //Invalid format
	assert(dtTest.to_string("yyyy-MM-dd HH:mm:ss tt") == "2015-10-14 15:12:13 PM");

	dtTest = datetime(2015, 2, 5, 1, 2, 3);
	assert(dtTest.to_string("yyyy-M-d") == "2015-2-5");
	assert(dtTest.to_string("yyyy-MM-dd") == "2015-02-05");
	assert(dtTest.to_string("yyyy-MM-dd H:m:s") == "2015-02-05 1:2:3");
	assert(dtTest.to_string("yyyy-MM-dd HH:mm:ss tt") == "2015-02-05 01:02:03 AM");
	assert(dtTest.to_string("yyyy-MM-dd hh:mm:ss tt") == "2015-02-05 01:02:03 AM");
	assert(dtTest.to_string("yyyy-MM-dd h:mm:ss tt") == "2015-02-05 1:02:03 AM");

	dtTest = datetime(2015, 2, 5, 0, 0, 0);
	assert(dtTest.to_string("yyyy-MM-dd hh:mm:ss tt") == "2015-02-05 12:00:00 AM");
	assert(dtTest.to_string("yyyy-MM-dd h:mm:ss tt") == "2015-02-05 12:00:00 AM");
}

void test_operator_minus()
{
	datetime date1(2016, 12, 31);
	datetime date2(2016, 12, 25);
	timespan ts1 = date1 - date2;
	assert(ts1.get_days() == 6);
	date1 = datetime(2016, 12, 31, 11, 0, 0);
	date2 = datetime(2016, 12, 25, 13, 0, 0);
	ts1 = date2 - date1;
	assert(ts1.get_days() == -5);
	assert(ts1.get_hours() == -22);
	date1 = datetime(2016, 12, 31, 11, 55, 12);
	date2 = datetime(2016, 12, 25, 13, 32, 5);
	ts1 = date2 - date1;
	assert(ts1.get_days() == -5);
	assert(ts1.get_hours() == -22);
	assert(ts1.get_minutes() == -23);
	assert(ts1.get_seconds() == -7);
	date1 = datetime(2016, 12, 31, 11, 32, 5);
	date2 = datetime(2016, 12, 25, 13, 55, 12);
	ts1 = date2 - date1;
	assert(ts1.get_days() == -5);
	assert(ts1.get_hours() == -21);
	assert(ts1.get_minutes() == -36);
	assert(ts1.get_seconds() == -53);
	date1 = datetime(2016, 12, 31, 13, 32, 5);
	date2 = datetime(2016, 12, 25, 11, 55, 12);
	ts1 = date2 - date1;
	assert(ts1.get_days() == -6);
	assert(ts1.get_hours() == -1);
	assert(ts1.get_minutes() == -36);
	assert(ts1.get_seconds() == -53);
	date1 = datetime(2016, 12, 31);
	date2 = datetime(2016, 11, 25);
	ts1 = date2 - date1;
	assert(ts1.get_days() == -36);
	assert(ts1.get_hours() == 0);
	assert(ts1.get_minutes() == 0);
	assert(ts1.get_seconds() == 0);
	date1 = datetime(2016, 12, 31);
	date2 = datetime(2015, 11, 25);
	ts1 = date2 - date1;
	assert(ts1.get_days() == -402);
	assert(ts1.get_hours() == 0);
	assert(ts1.get_minutes() == 0);
	assert(ts1.get_seconds() == 0);
	date1 = datetime(2016, 11, 25);
	date2 = datetime(2016, 12, 5);
	ts1 = date2 - date1;
	assert(ts1.get_days() == 10);
	assert(ts1.get_hours() == 0);
	assert(ts1.get_minutes() == 0);
	assert(ts1.get_seconds() == 0);
	date1 = datetime(2016, 12, 31, 7, 32, 5);
	date2 = datetime(2016, 12, 31, 14, 55, 12);
	ts1 = date2 - date1;
	assert(ts1.get_days() == 0);
	assert(ts1.get_hours() == 7);
	assert(ts1.get_minutes() == 23);
	assert(ts1.get_seconds() == 7);
}

void test_static_is_leapyear()
{
	assert(datetime::is_leapyear(2000));
	assert(datetime::is_leapyear(2004));
	assert(!datetime::is_leapyear(1700));
}

void datetime_unittest()
{
	test_constructor();
	test_to_string();
	test_to_shortdate_string();
	test_add_days();
	test_add_months();
	test_add_years();
	test_is_leapyear();
	test_add_hours();
	test_add_minutes();
	test_add_seconds();
	test_operator_less();
	test_operator_less_equal();
	test_operator_greater();
	test_operator_greater_equal();
	test_operator_equal();
	test_operator_not_equal();
	test_operator_minus();
	test_get_weekday();
	test_parse();
	test_tostring_format();
	test_static_is_leapyear();
}
