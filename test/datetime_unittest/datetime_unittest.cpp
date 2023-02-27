#include "../../src/datetime.h"
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

TEST(datetime_parse, hh01WithoutAMPMDesignator_ReturnOK)
{
	datetime dtTest = datetime::parse(string("yyyyMMddhhmmss"), string("20160818011442"));
	ASSERT_EQ(2016, dtTest.get_year());
	ASSERT_EQ(8, dtTest.get_month());
	ASSERT_EQ(18, dtTest.get_day());
	ASSERT_EQ(1, dtTest.get_hour());
	ASSERT_EQ(14, dtTest.get_minute());
	ASSERT_EQ(42, dtTest.get_second());
}

TEST(datetime_parse, hh12WithoutAMPMDesignator_ReturnOK)
{
	datetime dtTest = datetime::parse(string("yyyyMMddhhmmss"), string("20160818121442"));
	ASSERT_EQ(2016, dtTest.get_year());
	ASSERT_EQ(8, dtTest.get_month());
	ASSERT_EQ(18, dtTest.get_day());
	ASSERT_EQ(0, dtTest.get_hour());
	ASSERT_EQ(14, dtTest.get_minute());
	ASSERT_EQ(42, dtTest.get_second());
}

TEST(datetime_parse, hh00WithoutAMPMDesignator_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTest = datetime::parse(string("yyyyMMddhhmmss"), string("20160818001442"));
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "hour must be between 1 and 12"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_parse, hh13WithoutAMPMDesignator_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTest = datetime::parse(string("yyyyMMddhhmmss"), string("20160818131442"));
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "hour must be between 1 and 12"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_parse, hh11WithoutAMPMDesignator_ReturnOK)
{
	datetime dtTest = datetime::parse(string("yyyyMMddhhmmss"), string("20160818111442"));
	ASSERT_EQ(2016, dtTest.get_year());
	ASSERT_EQ(8, dtTest.get_month());
	ASSERT_EQ(18, dtTest.get_day());
	ASSERT_EQ(11, dtTest.get_hour());
	ASSERT_EQ(14, dtTest.get_minute());
	ASSERT_EQ(42, dtTest.get_second());
}

TEST(datetime_parse, hh1WithoutAMPMDesignator_ReturnOK)
{
	datetime dtTest = datetime::parse(string("yyyyMMddhhmmss"), string("20160818011442"));
	ASSERT_EQ(2016, dtTest.get_year());
	ASSERT_EQ(8, dtTest.get_month());
	ASSERT_EQ(18, dtTest.get_day());
	ASSERT_EQ(1, dtTest.get_hour());
	ASSERT_EQ(14, dtTest.get_minute());
	ASSERT_EQ(42, dtTest.get_second());
}

TEST(datetime_parse, hh1AM_ReturnOK)
{
	datetime dtTest = datetime::parse(string("yyyyMMddhhmmsstt"), string("20160818011442AM"));
	ASSERT_EQ(2016, dtTest.get_year());
	ASSERT_EQ(8, dtTest.get_month());
	ASSERT_EQ(18, dtTest.get_day());
	ASSERT_EQ(1, dtTest.get_hour());
	ASSERT_EQ(14, dtTest.get_minute());
	ASSERT_EQ(42, dtTest.get_second());
}

TEST(datetime_parse, hh1PM_ReturnOK)
{
	datetime dtTest = datetime::parse(string("yyyyMMddhhmmsstt"), string("20160818011442PM"));
	ASSERT_EQ(2016, dtTest.get_year());
	ASSERT_EQ(8, dtTest.get_month());
	ASSERT_EQ(18, dtTest.get_day());
	ASSERT_EQ(13, dtTest.get_hour());
	ASSERT_EQ(14, dtTest.get_minute());
	ASSERT_EQ(42, dtTest.get_second());
}

TEST(datetime_parse, hh12PM_ReturnOK)
{
	datetime dtTest = datetime::parse(string("yyyyMMddhhmmsstt"), string("20160818121442PM"));
	ASSERT_EQ(2016, dtTest.get_year());
	ASSERT_EQ(8, dtTest.get_month());
	ASSERT_EQ(18, dtTest.get_day());
	ASSERT_EQ(12, dtTest.get_hour());
	ASSERT_EQ(14, dtTest.get_minute());
	ASSERT_EQ(42, dtTest.get_second());
}

TEST(datetime_parse, hh11PM_ReturnOK)
{
	datetime dtTest = datetime::parse(string("yyyyMMddhhmmsstt"), string("20160818111442PM"));
	ASSERT_EQ(2016, dtTest.get_year());
	ASSERT_EQ(8, dtTest.get_month());
	ASSERT_EQ(18, dtTest.get_day());
	ASSERT_EQ(23, dtTest.get_hour());
	ASSERT_EQ(14, dtTest.get_minute());
	ASSERT_EQ(42, dtTest.get_second());
}

TEST(datetime_parse, hh13WithInvalidAMPMDesignator_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTest = datetime::parse(string("yyyyMMddhhmmsstt"), string("20160818111442EM"));
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "invalid value for period"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_to_string, EmptyFormat_ThrowInvalidArgumentException)
{
	try 
	{
		datetime dtTest = datetime();
		dtTest.to_string("");
		FAIL();
	}
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "format"); 
	}
	catch (...) { FAIL(); }
}

TEST(datetime_to_string, MultipleTests20151014151213_ReturnOK)
{
	datetime dtTest = datetime(2015, 10, 14, 15, 12, 13);
	ASSERT_STREQ(dtTest.to_string("/02-yyyy/MM-dd").c_str(), "/02-2015/10-14");
	ASSERT_STREQ(dtTest.to_string("yyyy-MM-dd").c_str(), "2015-10-14");
	ASSERT_STREQ(dtTest.to_string("yyyy-M-d").c_str(), "2015-10-14");
	ASSERT_STREQ(dtTest.to_string("yyyy MM dd").c_str(), "2015 10 14");
	ASSERT_STREQ(dtTest.to_string("dd/MM/yyyy").c_str(), "14/10/2015");
	ASSERT_STREQ(dtTest.to_string("yyyy").c_str(), "2015");
	ASSERT_STREQ(dtTest.to_string("MM").c_str(), "10");
	ASSERT_STREQ(dtTest.to_string("dd").c_str(), "14");
	ASSERT_STREQ(dtTest.to_string("yyyy-MM-dd HH:mm:ss").c_str(), "2015-10-14 15:12:13");
	ASSERT_STREQ(dtTest.to_string("yyyy-MM-dd hh:mm:ss tt").c_str(), "2015-10-14 03:12:13 PM");
	ASSERT_STREQ(dtTest.to_string("yyyy-MM-dd h:mm:ss tt").c_str(), "2015-10-14 3:12:13 PM");
	ASSERT_STREQ(dtTest.to_string("yyyy-MM-dd H:m:s").c_str(), "2015-10-14 15:12:13");
	ASSERT_STREQ(dtTest.to_string("HH:mm:ss").c_str(), "15:12:13");
	ASSERT_STREQ(dtTest.to_string("aaaa").c_str(), ""); //Invalid format
	ASSERT_STREQ(dtTest.to_string("aaaa-ii").c_str(), "-"); //Invalid format
	ASSERT_STREQ(dtTest.to_string("yyyy-MM-dd HH:mm:ss tt").c_str(), "2015-10-14 15:12:13 PM");
}

TEST(datetime_to_string, MultipleTests201525123_ReturnOK)
{
	datetime dtTest = datetime(2015, 2, 5, 1, 2, 3);
	ASSERT_STREQ(dtTest.to_string("yyyy-M-d").c_str(), "2015-2-5");
	ASSERT_STREQ(dtTest.to_string("yyyy-MM-dd").c_str(), "2015-02-05");
	ASSERT_STREQ(dtTest.to_string("yyyy-MM-dd H:m:s").c_str(), "2015-02-05 1:2:3");
	ASSERT_STREQ(dtTest.to_string("yyyy-MM-dd HH:mm:ss tt").c_str(), "2015-02-05 01:02:03 AM");
	ASSERT_STREQ(dtTest.to_string("yyyy-MM-dd hh:mm:ss tt").c_str(), "2015-02-05 01:02:03 AM");
	ASSERT_STREQ(dtTest.to_string("yyyy-MM-dd h:mm:ss tt").c_str(), "2015-02-05 1:02:03 AM");
}

TEST(datetime_to_string, MultipleTests201525000_ReturnOK)
{
	datetime dtTest = datetime(2015, 2, 5, 0, 0, 0);
	ASSERT_STREQ(dtTest.to_string("yyyy-MM-dd hh:mm:ss tt").c_str(), "2015-02-05 12:00:00 AM");
	ASSERT_STREQ(dtTest.to_string("yyyy-MM-dd h:mm:ss tt").c_str(), "2015-02-05 12:00:00 AM");
	ASSERT_STREQ(dtTest.to_string("yy-MM-dd h:mm:ss tt").c_str(), "15-02-05 12:00:00 AM"); //Format yy
}

TEST(datetime_to_string, Test191325000_ReturnOK)
{
	datetime dtTest = datetime(1913, 2, 5, 0, 0, 0);
	ASSERT_STREQ(dtTest.to_string("yy/MM/dd h:mm:ss tt").c_str(), "13/02/05 12:00:00 AM"); //Format yy
}

TEST(datetime_operator_minus, Difference6Days_ReturnOK)
{
	datetime date1(2016, 12, 31);
	datetime date2(2016, 12, 25);
	timespan ts1 = date1 - date2;
	ASSERT_EQ(ts1.get_days(), 6);
}

TEST(datetime_operator_minus, DifferenceMinus5DaysMinus22Hours_ReturnOK)
{
	datetime date1 = datetime(2016, 12, 31, 11, 0, 0);
	datetime date2 = datetime(2016, 12, 25, 13, 0, 0);
	timespan ts1 = date2 - date1;
	ASSERT_EQ(ts1.get_days(), -5);
	ASSERT_EQ(ts1.get_hours(), -22);
}

TEST(datetime_operator_minus, DifferenceMinus5DaysMinus22HoursMinus23MinsMinus7Secs_ReturnOK)
{
	datetime date1 = datetime(2016, 12, 31, 11, 55, 12);
	datetime date2 = datetime(2016, 12, 25, 13, 32, 5);
	timespan ts1 = date2 - date1;
	ASSERT_EQ(ts1.get_days(), -5);
	ASSERT_EQ(ts1.get_hours(), -22);
	ASSERT_EQ(ts1.get_minutes(), -23);
	ASSERT_EQ(ts1.get_seconds(), -7);
}

TEST(datetime_operator_minus, DifferenceMinus5DaysMinus21HoursMinus36MinsMinus53Secs_ReturnOK)
{
	datetime date1 = datetime(2016, 12, 31, 11, 32, 5);
	datetime date2 = datetime(2016, 12, 25, 13, 55, 12);
	timespan ts1 = date2 - date1;
	ASSERT_EQ(ts1.get_days(), -5);
	ASSERT_EQ(ts1.get_hours(), -21);
	ASSERT_EQ(ts1.get_minutes(), -36);
	ASSERT_EQ(ts1.get_seconds(), -53);
}

TEST(datetime_operator_minus, DifferenceMinus6DaysMinus1HoursMinus36MinsMinus53Secs_ReturnOK)
{
	datetime date1 = datetime(2016, 12, 31, 13, 32, 5);
	datetime date2 = datetime(2016, 12, 25, 11, 55, 12);
	timespan ts1 = date2 - date1;
	ASSERT_EQ(ts1.get_days(), -6);
	ASSERT_EQ(ts1.get_hours(), -1);
	ASSERT_EQ(ts1.get_minutes(), -36);
	ASSERT_EQ(ts1.get_seconds(), -53);
}

TEST(datetime_operator_minus, DifferenceMinus36Days0Hours0Mins0Secs_ReturnOK)
{
	datetime date1 = datetime(2016, 12, 31);
	datetime date2 = datetime(2016, 11, 25);
	timespan ts1 = date2 - date1;
	ASSERT_EQ(ts1.get_days(), -36);
	ASSERT_EQ(ts1.get_hours(), 0);
	ASSERT_EQ(ts1.get_minutes(), 0);
	ASSERT_EQ(ts1.get_seconds(), 0);
}

TEST(datetime_operator_minus, DifferenceMinus402Days0Hours0Mins0Secs_ReturnOK)
{
	datetime date1 = datetime(2016, 12, 31);
	datetime date2 = datetime(2015, 11, 25);
	timespan ts1 = date2 - date1;
	ASSERT_EQ(ts1.get_days(), -402);
	ASSERT_EQ(ts1.get_hours(), 0);
	ASSERT_EQ(ts1.get_minutes(), 0);
	ASSERT_EQ(ts1.get_seconds(), 0);
}

TEST(datetime_operator_minus, Difference10Days0Hours0Mins0Secs_ReturnOK)
{
	datetime date1 = datetime(2016, 11, 25);
	datetime date2 = datetime(2016, 12, 5);
	timespan ts1 = date2 - date1;
	assert(ts1.get_days() == 10);
	assert(ts1.get_hours() == 0);
	assert(ts1.get_minutes() == 0);
	assert(ts1.get_seconds() == 0);
}

TEST(datetime_operator_minus, Difference0Days7Hours23Mins7Secs_ReturnOK)
{
	datetime date1 = datetime(2016, 12, 31, 7, 32, 5);
	datetime date2 = datetime(2016, 12, 31, 14, 55, 12);
	timespan ts1 = date2 - date1;
	assert(ts1.get_days() == 0);
	assert(ts1.get_hours() == 7);
	assert(ts1.get_minutes() == 23);
	assert(ts1.get_seconds() == 7);
}

TEST(datetime_operator_minus, Difference2Days17Hours1Mins58Secs_ReturnOK)
{
	datetime date1 = datetime(2023, 2, 27, 15, 58, 2);
	datetime date2 = datetime(2023, 3, 2, 9, 0, 0);
	timespan ts1 = date2 - date1;
	assert(ts1.get_days() == 2);
	assert(ts1.get_hours() == 17);
	assert(ts1.get_minutes() == 1);
	assert(ts1.get_seconds() == 58);
	assert(ts1.get_total_seconds() == 61318 + 3600 * 24 * 2);
}

TEST(datetime_static_is_leapyear, Year2000_ReturnTrue)
{
	ASSERT_TRUE(datetime::is_leapyear(2000));
}

TEST(datetime_static_is_leapyear, Year2004_ReturnTrue)
{
	ASSERT_TRUE(datetime::is_leapyear(2004));
}

TEST(datetime_static_is_leapyear, Year1700_ReturnFalse)
{
	ASSERT_FALSE(datetime::is_leapyear(1700));
}