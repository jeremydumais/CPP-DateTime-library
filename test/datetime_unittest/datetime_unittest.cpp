#include "../../src/datetime.h"
#include <iostream>
#include <assert.h>
#include <cstring>
#include <exception>
#include <gtest/gtest.h>

using namespace jed_utils;
using namespace std;

TEST(datetime_constructor, ValidDateTime20150214_ReturnOK)
{
	datetime dtTest(2015, 02, 14);
	ASSERT_EQ(2015, dtTest.get_year());
	ASSERT_EQ(2, dtTest.get_month());
	ASSERT_EQ(14, dtTest.get_day());
	ASSERT_EQ(0, dtTest.get_hour());
	ASSERT_EQ(0, dtTest.get_minute());
	ASSERT_EQ(0, dtTest.get_second());
}

TEST(datetime_constructor, ValidDateTime20150214WithHour24Format_ReturnOK)
{
	datetime dtTest(2015, 02, 14, 23, 12, 11);
	ASSERT_EQ(2015, dtTest.get_year());
	ASSERT_EQ(2, dtTest.get_month());
	ASSERT_EQ(14, dtTest.get_day());
	ASSERT_EQ(23, dtTest.get_hour());
	ASSERT_EQ(12, dtTest.get_minute());
	ASSERT_EQ(11, dtTest.get_second());
}

TEST(datetime_constructor, InvalidMonthZero_ThrowInvalidArgumentException)
{
	try
	{
		datetime dtTestExept(2015, 00, 14); 
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "month must be between 1 and 12");
	}
	catch (...) { FAIL(); }
}

TEST(datetime_constructor, InvalidMonthThirteen_ThrowInvalidArgumentException)
{
	try
	{
		datetime dtTestExept(2015, 13, 14); 
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "month must be between 1 and 12");
	}
	catch (...) { FAIL(); }
}

TEST(datetime_constructor, InvalidDayZero_ThrowInvalidArgumentException)
{
	try
	{
		datetime dtTestExept(2015, 1, 0); 
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "day is out of range");
	}
	catch (...) { FAIL(); }
}

TEST(datetime_constructor, InvalidDay32ForMonthsWith31Days_ThrowInvalidArgumentException)
{
	int month_to_check_31[] = { 1,3,5,7,8,10,12 };
	for (int i : month_to_check_31)
	{
		try 
		{
			datetime dtTestExept(2015, i, 32);
			FAIL();
		}
		catch (const std::invalid_argument e) {
			ASSERT_STREQ(e.what(), "day is out of range");
		}
		catch (...) { FAIL(); }
	}
}

TEST(datetime_constructor, InvalidDay31ForMonthsWith30Days_ThrowInvalidArgumentException)
{
	int month_to_check_30[] = { 4,6,9,11 };
	for (int i : month_to_check_30)
	{
		try 
		{
			datetime dtTestExept(2015, i, 31);
			FAIL();
		}
		catch (const std::invalid_argument e) {
			ASSERT_STREQ(e.what(), "day is out of range"); 
		}
		catch (...) { FAIL(); }
	}
}

TEST(datetime_constructor, InvalidDay30ForFebruary_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTestExept(2000, 2, 30);
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "day is out of range"); }
	catch (...) { FAIL(); }
}

TEST(datetime_constructor, ValidLeapYear_ReturnOK)
{
	datetime dtTest = datetime(2000, 02, 29);
	ASSERT_EQ(2000, dtTest.get_year());
	ASSERT_EQ(2, dtTest.get_month());
	ASSERT_EQ(29, dtTest.get_day());
	ASSERT_EQ(0, dtTest.get_hour());
	ASSERT_EQ(0, dtTest.get_minute());
	ASSERT_EQ(0, dtTest.get_second());
	ASSERT_TRUE(dtTest.is_leapyear());
}

TEST(datetime_constructor, InvalidDay29ForFebruaryNonLeapYear_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTestExept(2001, 2, 29); 
		FAIL();
	}
	catch (const std::invalid_argument e) {
		assert(strcmp(e.what(), "day is out of range") == 0); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_constructor, InvalidHourMinus1_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTestExept(2015, 1, 14, -1);
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "hour must be between 0 and 23"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_constructor, InvalidHour24_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTestExept(2015, 1, 14, 24);
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "hour must be between 0 and 23"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_constructor, InvalidMinuteMinus1_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTestExept(2015, 1, 14, 1, -1);
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "minute must be between 0 and 59"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_constructor, InvalidMinute60_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTestExept(2015, 1, 14, 1, 60);
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "minute must be between 0 and 59"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_constructor, InvalidSecondMinus1_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTestExept(2015, 1, 14, 1, 1, -1);
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "second must be between 0 and 59"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_constructor, InvalidSecond60_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTestExept(2015, 1, 14, 1, 1, 60);
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "second must be between 0 and 59"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_constructor, InvalidDayPeriod_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTestExept(2015, 1, 14, 1, 1, 59, static_cast<period>(3)); 
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "the selected period is out of range"); 
	}
	catch (...) { FAIL(); }


}

TEST(datetime_to_string, ValidDate1_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14);
	ASSERT_STREQ(dtTest.to_string().c_str(), "2015-02-14 00:00:00");
}

TEST(datetime_to_string, ValidDate2_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14, 11, 7, 2);
	ASSERT_STREQ(dtTest.to_string().c_str(), "2015-02-14 11:07:02");
}

TEST(datetime_to_string, ValidDate3_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14, 11, 55, 45);
	ASSERT_STREQ(dtTest.to_string().c_str(), "2015-02-14 11:55:45");
}

TEST(datetime_to_shortdate_string, ValidDate1_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14);
	ASSERT_STREQ(dtTest.to_shortdate_string().c_str(), "2015-02-14");
}

TEST(datetime_to_shortdate_string, ValidDate2_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14, 11, 7, 2);
	ASSERT_STREQ(dtTest.to_shortdate_string().c_str(), "2015-02-14");
}

TEST(datetime_to_shortdate_string, ValidDate3_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14, 11, 55, 45);
	ASSERT_STREQ(dtTest.to_shortdate_string().c_str(), "2015-02-14");
}

TEST(datetime_add_days, Add2Days_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14);
	dtTest.add_days(2);
	ASSERT_STREQ(dtTest.to_shortdate_string().c_str(), "2015-02-16");
}

TEST(datetime_add_days, Add5Days_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 27, 11, 7, 2);
	dtTest.add_days(5);
	ASSERT_STREQ(dtTest.to_shortdate_string().c_str(), "2015-03-04");
}

TEST(datetime_add_days, AddMinus3Days_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 02, 11, 7, 2);
	dtTest.add_days(-3);
	ASSERT_STREQ(dtTest.to_shortdate_string().c_str(), "2015-01-30");
}

TEST(datetime_add_months, Add2Months_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14);
	dtTest.add_months(2);
	ASSERT_STREQ(dtTest.to_shortdate_string().c_str(), "2015-04-14");
}

TEST(datetime_add_months, AddMinus2Months_ReturnOK)
{
	datetime dtTest = datetime(2015, 04, 14);
	dtTest.add_months(-2);
	ASSERT_STREQ(dtTest.to_shortdate_string().c_str(), "2015-02-14");
}

TEST(datetime_add_months, Add3Months_ReturnOK)
{
	datetime dtTest = datetime(2015, 11, 14);
	dtTest.add_months(3);
	ASSERT_STREQ(dtTest.to_shortdate_string().c_str(), "2016-02-14");
}

TEST(datetime_add_months, Add23Months_ReturnOK)
{
	datetime dtTest = datetime(2015, 11, 14);
	dtTest.add_months(23);
	ASSERT_STREQ(dtTest.to_shortdate_string().c_str(), "2017-10-14");
}

TEST(datetime_add_months, AddMinus13Months_ReturnOK)
{
	datetime dtTest = datetime(2015, 11, 14);
	dtTest.add_months(-13);
	ASSERT_STREQ(dtTest.to_shortdate_string().c_str(), "2014-10-14");
}

TEST(datetime_add_years, Add2Years_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14);
	dtTest.add_years(2);
	ASSERT_STREQ(dtTest.to_shortdate_string().c_str(), "2017-02-14");
}

TEST(datetime_add_years, AddMinus2Years_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14);
	dtTest.add_years(-2);
	ASSERT_STREQ(dtTest.to_shortdate_string().c_str(), "2013-02-14");
}

TEST(datetime_is_leapyear, Year2000_ReturnOK)
{
	datetime dtTest(2000, 01, 01);
	ASSERT_TRUE(dtTest.is_leapyear());
}

TEST(datetime_is_leapyear, Year2004_ReturnOK)
{
	datetime dtTest(2004, 01, 01);
	ASSERT_TRUE(dtTest.is_leapyear());
}

TEST(datetime_is_leapyear, Year1700_ReturnOK)
{
	datetime dtTest(1700, 01, 01);
	ASSERT_FALSE(dtTest.is_leapyear());
}

TEST(datetime_add_hours, Add2Hours_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14, 11);
	dtTest.add_hours(2);
	ASSERT_STREQ(dtTest.to_string().c_str(), "2015-02-14 13:00:00");
}

TEST(datetime_add_hours, Add2HoursFrom23h00_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14, 23);
	dtTest.add_hours(2);
	ASSERT_STREQ(dtTest.to_string().c_str(), "2015-02-15 01:00:00");
}

TEST(datetime_add_hours, AddMinus48Hours_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14, 01);
	dtTest.add_hours(-48);
	ASSERT_STREQ(dtTest.to_string().c_str(), "2015-02-12 01:00:00");
}

TEST(datetime_add_minutes, Add30Minutes_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14, 11, 11);
	dtTest.add_minutes(30);
	ASSERT_STREQ(dtTest.to_string().c_str(), "2015-02-14 11:41:00");
}

TEST(datetime_add_minutes, Add90Minutes_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14, 11, 00);
	dtTest.add_minutes(90);
	ASSERT_STREQ(dtTest.to_string().c_str(), "2015-02-14 12:30:00");
}

TEST(datetime_add_minutes, AddMinus90Minutes_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14, 00, 00);
	dtTest.add_minutes(-90);
	ASSERT_STREQ(dtTest.to_string().c_str(), "2015-02-13 22:30:00");
}

TEST(datetime_add_seconds, Add30Seconds_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14, 11, 11, 11);
	dtTest.add_seconds(30);
	ASSERT_STREQ(dtTest.to_string().c_str(), "2015-02-14 11:11:41");
}

TEST(datetime_add_seconds, Add90Seconds_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14, 11, 11, 00);
	dtTest.add_seconds(90);
	ASSERT_STREQ(dtTest.to_string().c_str(), "2015-02-14 11:12:30");
}

TEST(datetime_add_seconds, AddMinus90Seconds_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 00);
	dtTest.add_seconds(-90);
	ASSERT_STREQ(dtTest.to_string().c_str(), "2015-02-14 13:58:30");
}

TEST(datetime_operator_less, LessThan1Second_ReturnTrue)
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 00);
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 01);
	ASSERT_LT(dtTest, dtTest2);
}

TEST(datetime_operator_less, LessThanNow_ReturnTrue)
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 00);
	datetime dtTest2 = datetime();
	ASSERT_LT(dtTest, dtTest2);
}

TEST(datetime_operator_less, EqualValues_ReturnFalse)
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 00);
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	ASSERT_FALSE(dtTest < dtTest2);
}

TEST(datetime_operator_less, GreaterValue_ReturnFalse)
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 01);
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	ASSERT_FALSE(dtTest < dtTest2);
}

TEST(datetime_operator_less_equal, LessEqualThan1Second_ReturnTrue)
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 00);
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 01);
	ASSERT_LE(dtTest, dtTest2);
}

TEST(datetime_operator_less_equal, LessEqualThanNow_ReturnTrue)
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 00);
	datetime dtTest2 = datetime();
	ASSERT_LE(dtTest, dtTest2);
}

TEST(datetime_operator_less_equal, LessEqualThanEqualValues_ReturnTrue)
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 00);
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	ASSERT_LE(dtTest, dtTest2);
}

TEST(datetime_operator_less_equal, GreaterValue_ReturnFalse)
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 01);
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	ASSERT_FALSE(dtTest <= dtTest2);
}

TEST(datetime_operator_greater, GreaterThan1Second_ReturnTrue)
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 01);
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	ASSERT_GT(dtTest, dtTest2);
}

TEST(datetime_operator_greater, NowGreaterThan_ReturnTrue)
{
	datetime dtTest = datetime();
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	ASSERT_GT(dtTest, dtTest2);
}

TEST(datetime_operator_greater, EqualValues_ReturnFalse)
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 00);
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	ASSERT_FALSE(dtTest > dtTest2);
}

TEST(datetime_operator_greater_equal, GreaterEqualThan1Second_ReturnTrue)
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 01);
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	ASSERT_GE(dtTest, dtTest2);
}

TEST(datetime_operator_greater_equal, NowGreaterEqualThan_ReturnTrue)
{
	datetime dtTest = datetime();
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	ASSERT_GE(dtTest, dtTest2);
}

TEST(datetime_operator_greater_equal, GreaterEqualThanEqualValues_ReturnTrue)
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 00);
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 00);
	ASSERT_GE(dtTest, dtTest2);
}

TEST(datetime_operator_greater_equal, GreaterEqualThanGreaterValue1Second_ReturnFalse)
{
	datetime dtTest = datetime(2015, 02, 14, 14, 00, 00);
	datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 01);
	ASSERT_FALSE(dtTest >= dtTest2);
}

TEST(datetime_operator_equal, EqualValuesCase1_ReturnTrue)
{
	ASSERT_EQ(datetime(2017, 1, 8, 15, 28, 23), datetime(2017, 1, 8, 15, 28, 23));
}

TEST(datetime_operator_equal, EqualValuesCase2_ReturnTrue)
{
	ASSERT_EQ(datetime(2016, 12, 31, 23, 59, 59), datetime(2016, 12, 31, 23, 59, 59));
}

TEST(datetime_operator_equal, NotEqualValuesCase2_ReturnFalse)
{
	ASSERT_FALSE(datetime(2016, 12, 31, 23, 59, 58) == datetime(2016, 12, 31, 23, 59, 59));
}

TEST(datetime_operator_not_equal, EqualValuesCase1_ReturnFalse)
{
	ASSERT_FALSE(datetime(2017, 1, 8, 15, 28, 23) != datetime(2017, 1, 8, 15, 28, 23));
}

TEST(datetime_operator_not_equal, EqualValuesCase2_ReturnFalse)
{
	ASSERT_FALSE(datetime(2016, 12, 31, 23, 59, 59) != datetime(2016, 12, 31, 23, 59, 59));
}

TEST(datetime_operator_not_equal, NotEqualValuesDifferentSecond_ReturnTrue)
{
	ASSERT_NE(datetime(2017, 1, 8, 15, 28, 23), datetime(2017, 1, 8, 15, 28, 22));
}

TEST(datetime_operator_not_equal, NotEqualValuesDifferentMinute_ReturnTrue)
{
	ASSERT_NE(datetime(2017, 1, 8, 15, 28, 23), datetime(2017, 1, 8, 15, 27, 23));
}

TEST(datetime_operator_not_equal, NotEqualValuesDifferentHour_ReturnTrue)
{
	ASSERT_NE(datetime(2017, 1, 8, 15, 28, 23), datetime(2017, 1, 8, 14, 28, 23));
}

TEST(datetime_operator_not_equal, NotEqualValuesDifferentDay_ReturnTrue)
{
	ASSERT_NE(datetime(2017, 1, 8, 15, 28, 23), datetime(2017, 1, 7, 15, 28, 23));
}

TEST(datetime_operator_not_equal, NotEqualValuesDifferentMonth_ReturnTrue)
{
	ASSERT_NE(datetime(2017, 1, 8, 15, 28, 23), datetime(2017, 2, 8, 15, 28, 23));
}

TEST(datetime_operator_not_equal, NotEqualValuesDifferentYear_ReturnTrue)
{
	ASSERT_NE(datetime(2017, 1, 8, 15, 28, 23), datetime(2016, 1, 8, 15, 28, 23));
}

TEST(datetime_get_weekday, GetSaturday_ReturnTrue)
{
	datetime dtTest = datetime(2015, 02, 14, 11, 11, 11);
	ASSERT_EQ(dtTest.get_weekday(), weekday::saturday);
}

TEST(datetime_get_weekday, GetSunday_ReturnOK)
{
	datetime dtTest = datetime(2015, 02, 15);
	ASSERT_EQ(dtTest.get_weekday(), weekday::sunday);
}

TEST(datetime_parse, YearOnly_ReturnOK)
{
	//Parse with year
	datetime dtTest = datetime::parse(string("yyyy"), string("2016"));
	ASSERT_EQ(dtTest.get_year(), 2016);
	ASSERT_EQ(dtTest.get_month(), 1);
	ASSERT_EQ(dtTest.get_day(), 1);
}

TEST(datetime_parse, YearAndMonthHyphen_ReturnOK)
{
	datetime dtTest = datetime::parse(string("yyyy-MM"), string("2016-04"));
	ASSERT_EQ(dtTest.get_year(), 2016);
	ASSERT_EQ(dtTest.get_month(), 4);
	ASSERT_EQ(dtTest.get_day(), 1);
}

TEST(datetime_parse, YearMonthDayStdSeparator_ReturnOK)
{
	datetime dtTest = datetime::parse(string("yyyy/MM/dd"), string("2016-08-18"));
	ASSERT_EQ(dtTest.get_year(), 2016);
	ASSERT_EQ(dtTest.get_month(), 8);
	ASSERT_EQ(dtTest.get_day(), 18);
}

TEST(datetime_parse, YearMonthDayHourStdSeparator_ReturnOK)
{
	datetime dtTest = datetime::parse(string("yyyy/MM/dd HH"), string("2016-08-18 23"));
	ASSERT_EQ(dtTest.get_year(), 2016);
	ASSERT_EQ(dtTest.get_month(), 8);
	ASSERT_EQ(dtTest.get_day(), 18);
	ASSERT_EQ(dtTest.get_hour(), 23);
}

TEST(datetime_parse, YearMonthDayHourMinuteStdSeparator_ReturnOK)
{
	datetime dtTest = datetime::parse(string("yyyy/MM/dd HH:mm"), string("2016-08-18 23:14"));
	ASSERT_EQ(dtTest.get_year(), 2016);
	ASSERT_EQ(dtTest.get_month(), 8);
	ASSERT_EQ(dtTest.get_day(), 18);
	ASSERT_EQ(dtTest.get_hour(), 23);
	ASSERT_EQ(dtTest.get_minute(), 14);
}

TEST(datetime_parse, YearMonthDayHourMinuteSecondStdSeparator_ReturnOK)
{
	datetime dtTest = datetime::parse(string("yyyy/MM/dd HH:mm:ss"), string("2016-08-18 23:14:42"));
	ASSERT_EQ(dtTest.get_year(), 2016);
	ASSERT_EQ(dtTest.get_month(), 8);
	ASSERT_EQ(dtTest.get_day(), 18);
	ASSERT_EQ(dtTest.get_hour(), 23);
	ASSERT_EQ(dtTest.get_minute(), 14);
	ASSERT_EQ(dtTest.get_second(), 42);
}

TEST(datetime_parse, YearMonthDayHourMinuteSecondNoSeparator_ReturnOK)
{
	datetime dtTest = datetime::parse(string("yyyyMMddHHmmss"), string("20160818231442"));
	ASSERT_EQ(dtTest.get_year(), 2016);
	ASSERT_EQ(dtTest.get_month(), 8);
	ASSERT_EQ(dtTest.get_day(), 18);
	ASSERT_EQ(dtTest.get_hour(), 23);
	ASSERT_EQ(dtTest.get_minute(), 14);
	ASSERT_EQ(dtTest.get_second(), 42);
}

TEST(datetime_parse, EmptyFormatEmptyValue_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTest = datetime::parse(string(""), string(""));
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "format"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_parse, WithAWordAsValue_ThrowRuntimeErrorException)
{
	try 
	{
		datetime dtTest = datetime::parse(string("yyyy"), string("allo"));
		FAIL();
	}
	catch (const std::runtime_error e) {
		ASSERT_STREQ(e.what(), "Unable to parse the mask yyyy"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_parse, ValueWithMonth00_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTest = datetime::parse(string("yyyy-MM-dd"), string("2017-00-01"));
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "month must be between 1 and 12"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_parse, ValueWithMonth13_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTest = datetime::parse(string("yyyy-MM-dd"), string("2017-13-01"));
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "month must be between 1 and 12"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_parse, ValueWithDay32_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTest = datetime::parse(string("yyyy-MM-dd"), string("2017-12-32"));
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "day is out of range"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_parse, ValueWithDay00_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTest = datetime::parse(string("yyyy-MM-dd"), string("2017-12-00"));
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "day is out of range"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_parse, ValueWithHour24_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTest = datetime::parse(string("yyyy-MM-dd HH"), string("2017-12-01 24"));
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "hour must be between 0 and 23"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_parse, ValueWithHourMinus1_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTest = datetime::parse(string("yyyy-MM-dd HH"), string("2017-12-01 -1"));
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "hour must be between 0 and 23"); 
	}
	catch (...) { FAIL(); }
}

void test_parse()
{
datetime dtTest;
	//Test hh 01 without AM/PM designator
	dtTest = datetime::parse(string("yyyyMMddhhmmss"), string("20160818011442"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 8);
	assert(dtTest.get_day() == 18);
	assert(dtTest.get_hour() == 1);
	assert(dtTest.get_minute() == 14);
	assert(dtTest.get_second() == 42);

	//Test hh 12 without AM/PM designator
	dtTest = datetime::parse(string("yyyyMMddhhmmss"), string("20160818121442"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 8);
	assert(dtTest.get_day() == 18);
	assert(dtTest.get_hour() == 0);
	assert(dtTest.get_minute() == 14);
	assert(dtTest.get_second() == 42);

	//Test hh 00 without AM/PM designator
	try
	{
		dtTest = datetime::parse(string("yyyyMMddhhmmss"), string("20160818001442"));
		assert(false);
	}
	catch (invalid_argument& err)
	{
		assert(strcmp(err.what(), "hour must be between 1 and 12") == 0);
	}
	catch (...) { assert(false); }

	//Test hh 13 without AM/PM designator
	try
	{
		dtTest = datetime::parse(string("yyyyMMddhhmmss"), string("20160818131442"));
		assert(false);
	}
	catch (invalid_argument& err)
	{
		assert(strcmp(err.what(), "hour must be between 1 and 12") == 0);
	}
	catch (...) { assert(false); }

	//Test hh 12 without AM/PM designator
	dtTest = datetime::parse(string("yyyyMMddhhmmss"), string("20160818121442"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 8);
	assert(dtTest.get_day() == 18);
	assert(dtTest.get_hour() == 0);
	assert(dtTest.get_minute() == 14);
	assert(dtTest.get_second() == 42);

	//Test hh 11 without AM/PM designator
	dtTest = datetime::parse(string("yyyyMMddhhmmss"), string("20160818111442"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 8);
	assert(dtTest.get_day() == 18);
	assert(dtTest.get_hour() == 11);
	assert(dtTest.get_minute() == 14);
	assert(dtTest.get_second() == 42);

	//Test hh 1 without AM/PM designator
	dtTest = datetime::parse(string("yyyyMMddhhmmss"), string("20160818011442"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 8);
	assert(dtTest.get_day() == 18);
	assert(dtTest.get_hour() == 1);
	assert(dtTest.get_minute() == 14);
	assert(dtTest.get_second() == 42);

	//Test hh 1 AM
	dtTest = datetime::parse(string("yyyyMMddhhmmsstt"), string("20160818011442AM"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 8);
	assert(dtTest.get_day() == 18);
	assert(dtTest.get_hour() == 1);
	assert(dtTest.get_minute() == 14);
	assert(dtTest.get_second() == 42);

	//Test hh 1 PM
	dtTest = datetime::parse(string("yyyyMMddhhmmsstt"), string("20160818011442PM"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 8);
	assert(dtTest.get_day() == 18);
	assert(dtTest.get_hour() == 13);
	assert(dtTest.get_minute() == 14);
	assert(dtTest.get_second() == 42);

	//Test hh 12 PM
	dtTest = datetime::parse(string("yyyyMMddhhmmsstt"), string("20160818121442PM"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 8);
	assert(dtTest.get_day() == 18);
	assert(dtTest.get_hour() == 12);
	assert(dtTest.get_minute() == 14);
	assert(dtTest.get_second() == 42);

	//Test hh 11 PM
	dtTest = datetime::parse(string("yyyyMMddhhmmsstt"), string("20160818111442PM"));
	assert(dtTest.get_year() == 2016);
	assert(dtTest.get_month() == 8);
	assert(dtTest.get_day() == 18);
	assert(dtTest.get_hour() == 23);
	assert(dtTest.get_minute() == 14);
	assert(dtTest.get_second() == 42);

	//Test hh 13 with invalide period
	try
	{
		dtTest = datetime::parse(string("yyyyMMddhhmmsstt"), string("20160818111442EM"));
		assert(false);
	}
	catch (invalid_argument& err)
	{
		assert(strcmp(err.what(), "invalid value for period") == 0);
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
	assert(dtTest.to_string("yy-MM-dd h:mm:ss tt") == "15-02-05 12:00:00 AM"); //Format yy

	dtTest = datetime(1913, 2, 5, 0, 0, 0);
	assert(dtTest.to_string("yy/MM/dd h:mm:ss tt") == "13/02/05 12:00:00 AM"); //Format yy
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