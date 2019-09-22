#include "../../src/datetime.h"
#include <gtest/gtest.h>

using namespace std;
using namespace jed_utils;

TEST(timespan_constructor, HourMinus24_ThrowInvalidArgumentException)
{
	try { timespan tsTest(0, -24, 0, 0); }
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "hours must be between 0 and 23");
	}
}

TEST(timespan_constructor, Hour24_ThrowInvalidArgumentException)
{
	try { timespan tsTest(0, 24, 0, 0); }
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "hours must be between 0 and 23");
	}
}

TEST(timespan_constructor, MinuteMinus60_ThrowInvalidArgumentException)
{
	try { timespan tsTest(0, 0, -60, 0); }
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "minutes must be between 0 and 59");
	}
}

TEST(timespan_constructor, Minute60_ThrowInvalidArgumentException)
{
	try { timespan tsTest(0, 0, 60, 0); }
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "minutes must be between 0 and 59");
	}
}

TEST(timespan_constructor, SecondMinus60_ThrowInvalidArgumentException)
{
	try { timespan tsTest(0, 0, 0, -60); }
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "seconds must be between 0 and 59");
	}
}

TEST(timespan_constructor, Second60_ThrowInvalidArgumentException)
{
	try { timespan tsTest(0, 0, 0, 60); }
	catch (const std::invalid_argument e) {
		ASSERT_STREQ(e.what(), "seconds must be between 0 and 59");
	}
}

TEST(timespan_constructor, Day0Hour0Minute0Second0_ReturnOK)
{
	timespan ts(0, 0, 0, 0);
	ASSERT_EQ(ts.get_days(), 0);
	ASSERT_EQ(ts.get_hours(), 0);
	ASSERT_EQ(ts.get_minutes(), 0);
	ASSERT_EQ(ts.get_seconds(), 0);
}

TEST(timespan_constructor, Day1our2Minute3Second4_ReturnOK)
{
	timespan ts(1, 2, 3, 4);
	ASSERT_EQ(ts.get_days(), 1);
	ASSERT_EQ(ts.get_hours(), 2);
	ASSERT_EQ(ts.get_minutes(), 3);
	ASSERT_EQ(ts.get_seconds(), 4);
}

TEST(timespan_get_total_seconds, Second15_ReturnOK)
{
	timespan ts(0, 0, 0, 15);
	ASSERT_EQ(ts.get_total_seconds(), 15);
}

TEST(timespan_get_total_seconds, Minute3Second15_ReturnOK)
{
	timespan ts(0, 0, 3, 15);
	ASSERT_EQ(ts.get_total_seconds(), 195);
}

TEST(timespan_get_total_seconds, Hour1Minute3Second15_ReturnOK)
{
	timespan ts(0, 1, 3, 15);
	ASSERT_EQ(ts.get_total_seconds(), 3795);
}

TEST(timespan_get_total_seconds, Day1Hour1Minute3Second15_ReturnOK)
{
	timespan ts(1, 1, 3, 15);
	ASSERT_EQ(ts.get_total_seconds(), 90195);
}

TEST(timespan_get_total_seconds, SecondMinus15_ReturnOK)
{
	timespan ts(0, 0, 0, -15);
	ASSERT_EQ(ts.get_total_seconds(), -15);
}

TEST(timespan_get_total_seconds, MinuteMinus3SecondMinus15_ReturnOK)
{
	timespan ts(0, 0, -3, -15);
	ASSERT_EQ(ts.get_total_seconds(), -195);
}

TEST(timespan_get_total_seconds, HourMinus1MinuteMinus3SecondMinus15_ReturnOK)
{
	timespan ts(0, -1, -3, -15);
	ASSERT_EQ(ts.get_total_seconds(), -3795);
}

TEST(timespan_get_total_seconds, DayMinus1HourMinus1MinuteMinus3SecondMinus15_ReturnOK)
{
	timespan ts(-1, -1, -3, -15);
	ASSERT_EQ(ts.get_total_seconds(), -90195);
}

TEST(timespan_get_total_minutes, Day0Hour0Minute0Second15_ReturnOK)
{
	timespan ts(0, 0, 0, 15);
	ASSERT_EQ(ts.get_total_minutes(), 0);
}

TEST(timespan_get_total_minutes, Day0Hour0Minute3Second15_ReturnOK)
{
	timespan ts(0, 0, 3, 15);
	ASSERT_EQ(ts.get_total_minutes(), 3);
}

TEST(timespan_get_total_minutes, Day0Hour1Minute3Second15_ReturnOK)
{
	timespan ts(0, 1, 3, 15);
	ASSERT_EQ(ts.get_total_minutes(), 63);
}

TEST(timespan_get_total_minutes, Day1Hour1Minute3Second15_ReturnOK)
{
	timespan ts(1, 1, 3, 15);
	ASSERT_EQ(ts.get_total_minutes(), 1503);
}

TEST(timespan_get_total_minutes, Day0Hour0Minute0SecondMinus15_ReturnOK)
{
	timespan ts(0, 0, 0, -15);
	ASSERT_EQ(ts.get_total_minutes(), 0);
}

TEST(timespan_get_total_minutes, Day0Hour0MinuteMinus3SecondMinus15_ReturnOK)
{
	timespan ts(0, 0, -3, -15);
	ASSERT_EQ(ts.get_total_minutes(), -3);
}

TEST(timespan_get_total_minutes, Day0HourMinus1MinuteMinus3SecondMinus15_ReturnOK)
{
	timespan ts(0, -1, -3, -15);
	ASSERT_EQ(ts.get_total_minutes(), -63);
}

TEST(timespan_get_total_minutes, DayMinus1HourMinus1MinuteMinus3SecondMinus15_ReturnOK)
{
	timespan ts(-1, -1, -3, -15);
	ASSERT_EQ(ts.get_total_minutes(), -1503);
}

TEST(timespan_get_total_hours, Day0Hour0Minute0Second15_ReturnOK)
{
	timespan ts(0, 0, 0, 15);
	ASSERT_EQ(ts.get_total_hours(), 0);
}

TEST(timespan_get_total_hours, Day0Hour0Minute3Second15_ReturnOK)
{
	timespan ts(0, 0, 3, 15);
	ASSERT_EQ(ts.get_total_hours(), 0);
}

TEST(timespan_get_total_hours, Day0Hour1Minute3Second15_ReturnOK)
{
	timespan ts(0, 1, 3, 15);
	ASSERT_EQ(ts.get_total_hours(), 1);
}

TEST(timespan_get_total_hours, Day3Hour1Minute3Second15_ReturnOK)
{
	timespan ts(3, 1, 3, 15);
	ASSERT_EQ(ts.get_total_hours(), 73);
}




TEST(timespan_get_total_hours, Day0Hour0Minute0SecondMinus15_ReturnOK)
{
	timespan ts(0, 0, 0, -15);
	ASSERT_EQ(ts.get_total_hours(), 0);
}

TEST(timespan_get_total_hours, Day0Hour0MinuteMinus3SecondMinus15_ReturnOK)
{
	timespan ts(0, 0, -3, -15);
	ASSERT_EQ(ts.get_total_hours(), 0);
}

TEST(timespan_get_total_hours, Day0HourMinus1MinuteMinus3SecondMinus15_ReturnOK)
{
	timespan ts(0, -1, -3, -15);
	ASSERT_EQ(ts.get_total_hours(), -1);
}

TEST(timespan_get_total_hours, DayMinus3HourMinus1MinuteMinus3SecondMinus15_ReturnOK)
{
	timespan ts(-3, -1, -3, -15);
	ASSERT_EQ(ts.get_total_hours(), -73);
}

TEST(timespan_operator_less, Difference1Minute_ReturnOK)
{
	timespan ts1(3, 2, 1, 0);
	timespan ts2(3, 2, 0, 0);
	ASSERT_LT(ts2, ts1);
}

TEST(timespan_operator_less, OppositeNegative_ReturnOK)
{
	timespan ts1 = timespan(3, 2, 1, 1);
	timespan ts2 = timespan(-3, -2, -1, -1);
	ASSERT_LT(ts2, ts1);
}

TEST(timespan_operator_less, Difference1Second_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(4, 3, 2, 0);
	ASSERT_LT(ts2, ts1);
}

TEST(timespan_operator_less, Difference1Hour_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(4, 2, 2, 1);
	ASSERT_LT(ts2, ts1);
}

TEST(timespan_operator_less, Difference1Day_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(3, 3, 2, 1);
	ASSERT_LT(ts2, ts1);
}

TEST(timespan_operator_less, DifferenceAllFields_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(3, 5, 4, 6);
	ASSERT_LT(ts2, ts1);
}

TEST(timespan_operator_less_equal, Difference1Minute_ReturnOK)
{
	timespan ts1(3, 2, 1, 0);
	timespan ts2(3, 2, 0, 0);
	ASSERT_LE(ts2, ts1);
}

TEST(timespan_operator_less_equal, OppositeNegative_ReturnOK)
{
	timespan ts1 = timespan(3, 2, 1, 1);
	timespan ts2 = timespan(-3, -2, -1, -1);
	ASSERT_LE(ts2, ts1);
}

TEST(timespan_operator_less_equal, Difference1Second_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(4, 3, 2, 0);
	ASSERT_LE(ts2, ts1);
}

TEST(timespan_operator_less_equal, Difference1Hour_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(4, 2, 2, 1);
	ASSERT_LE(ts2, ts1);
}

TEST(timespan_operator_less_equal, Difference1Day_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(3, 3, 2, 1);
	ASSERT_LE(ts2, ts1);
}

TEST(timespan_operator_less_equal, DifferenceAllFields_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(3, 5, 4, 6);
	ASSERT_LE(ts2, ts1);
}

TEST(timespan_operator_less_equal, AllFieldsEquals_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(4, 3, 2, 1);
	ASSERT_LE(ts2, ts1);
}

TEST(timespan_operator_less_equal, AllFieldsEqualsNegative_ReturnOK)
{
	timespan ts1 = timespan(-4, -3, -2, -1);
	timespan ts2 = timespan(-4, -3, -2, -1);
	ASSERT_LE(ts2, ts1);
}

TEST(timespan_operator_less_equal, AllFieldsZero_ReturnOK)
{
	timespan ts1 = timespan(0, 0, 0, 0);
	timespan ts2 = timespan(0, 0, 0, 0);
	ASSERT_LE(ts2, ts1);
}

TEST(timespan_operator_greater, Difference1Minute_ReturnOK)
{
	timespan ts1(3, 2, 1, 0);
	timespan ts2(3, 2, 0, 0);
	ASSERT_GT(ts1, ts2);
}

TEST(timespan_operator_greater, OppositeNegative_ReturnOK)
{
	timespan ts1 = timespan(3, 2, 1, 1);
	timespan ts2 = timespan(-3, -2, -1, -1);
	ASSERT_GT(ts1, ts2);
}

TEST(timespan_operator_greater, Difference1Second_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(4, 3, 2, 0);
	ASSERT_GT(ts1, ts2);
}

TEST(timespan_operator_greater, Difference1Hour_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(4, 2, 2, 1);
	ASSERT_GT(ts1, ts2);
}

TEST(timespan_operator_greater, Difference1Day_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(3, 3, 2, 1);
	ASSERT_GT(ts1, ts2);
}

TEST(timespan_operator_greater, DifferenceAllFields_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(3, 5, 4, 6);
	ASSERT_GT(ts1, ts2);
}

TEST(timespan_operator_greater_equal, OppositeNegative_ReturnOK)
{
	timespan ts1 = timespan(3, 2, 1, 1);
	timespan ts2 = timespan(-3, -2, -1, -1);
	ASSERT_GE(ts1, ts2);
}

TEST(timespan_operator_greater_equal, Difference1Second_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(4, 3, 2, 0);
	ASSERT_GE(ts1, ts2);
}

TEST(timespan_operator_greater_equal, Difference1Minute_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(4, 3, 1, 1);
	ASSERT_GE(ts1, ts2);
}

TEST(timespan_operator_greater_equal, Difference1Hour_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(4, 2, 2, 1);
	ASSERT_GE(ts1, ts2);
}

TEST(timespan_operator_greater_equal, Difference1Day_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(3, 3, 2, 1);
	ASSERT_GE(ts1, ts2);
}

TEST(timespan_operator_greater_equal, DifferenceAllFields_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(3, 5, 4, 6);
	ASSERT_GE(ts1, ts2);
}

TEST(timespan_operator_greater_equal, AllFieldsEquals_ReturnOK)
{
	timespan ts1 = timespan(4, 3, 2, 1);
	timespan ts2 = timespan(4, 3, 2, 1);
	ASSERT_GE(ts1, ts2);
}

TEST(timespan_operator_greater_equal, AllFieldsEqualsNegative_ReturnOK)
{
	timespan ts1 = timespan(-4, -3, -2, -1);
	timespan ts2 = timespan(-4, -3, -2, -1);
	ASSERT_GE(ts1, ts2);
}

TEST(timespan_operator_greater_equal, AllFieldsEqualsZeroReverse_ReturnOK)
{
	timespan ts1 = timespan(0, 0, 0, 0);
	timespan ts2 = timespan(0, 0, 0, 0);
	ASSERT_GE(ts2, ts1);
}

TEST(timespan_operator_equal, AllFieldsEquals_ReturnOK)
{
	ASSERT_EQ(timespan(1, 2, 3, 4), timespan(1, 2, 3, 4));
}

TEST(timespan_operator_equal, AllFieldsEqualsNegative_ReturnTrue)
{
	ASSERT_TRUE(timespan(-1, -2, -3, -4) == timespan(-1, -2, -3, -4));
}

TEST(timespan_operator_equal, DifferenceSecond_ReturnFalse)
{
	ASSERT_FALSE(timespan(1, 2, 3, 4) == timespan(1, 2, 3, 3));
}

TEST(timespan_operator_equal, DifferenceMinute_ReturnFalse)
{
	ASSERT_FALSE(timespan(1, 2, 3, 4) == timespan(1, 2, 2, 4));
}

TEST(timespan_operator_equal, DifferenceHour_ReturnFalse)
{
	ASSERT_FALSE(timespan(1, 2, 3, 4) == timespan(1, 1, 3, 4));
}

TEST(timespan_operator_equal, DifferenceDay_ReturnFalse)
{
	ASSERT_FALSE(timespan(1, 2, 3, 4) == timespan(0, 2, 3, 4));
}

TEST(timespan_operator_not_equal, AllFieldsEqual_ReturnFalse)
{
	ASSERT_FALSE(timespan(1, 2, 3, 4) != timespan(1, 2, 3, 4));
}

TEST(timespan_operator_not_equal, AllFieldsEqualNegative_ReturnFalse)
{
	ASSERT_FALSE(timespan(-1, -2, -3, -4) != timespan(-1, -2, -3, -4));
}

TEST(timespan_operator_not_equal, DifferenceSecond_ReturnTrue)
{
	ASSERT_TRUE(timespan(1, 2, 3, 4) != timespan(1, 2, 3, 3));
}

TEST(timespan_operator_not_equal, DifferenceMinute_ReturnTrue)
{
	ASSERT_TRUE(timespan(1, 2, 3, 4) != timespan(1, 2, 2, 4));
}

TEST(timespan_operator_not_equal, DifferenceHour_ReturnTrue)
{
	ASSERT_TRUE(timespan(1, 2, 3, 4) != timespan(1, 1, 3, 4));
}

TEST(timespan_operator_not_equal, DifferenceDay_ReturnTrue)
{
	ASSERT_TRUE(timespan(1, 2, 3, 4) != timespan(0, 2, 3, 4));
}