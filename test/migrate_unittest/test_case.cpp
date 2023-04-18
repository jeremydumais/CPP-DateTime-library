#include "../../src/datetime.h"
#include <gtest/gtest.h>

using namespace jed_utils;
using namespace std;

/**
 * This migrate tests include unit tests for various member functions in the datetime class,
 * including add_years, add_months, add_days, add_hours, add_minutes, and add_seconds. 
 * 
 * The test cases cover different scenarios of time changes and boundary conditions. 
 * Additionally, there are unit tests for the parse function in the datetime class, which 
 * test the correctness of parsing time strings in different formats.
 * 
*/
TEST(test, testSetMonthOfYear_int_dstOverlapWinter_addZero)
{
    datetime test = datetime(2011, 10, 30, 2, 30, 0);
    test.add_hours(1);
    ASSERT_EQ("2011-10-30 03:30:00", test.to_string());
}

TEST(test, testParse_formatter)
{
    datetime test = datetime(2010, 6, 30, 13, 0);
    ASSERT_EQ(test.to_string("yyyy--dd MM HH"), "2010--30 06 13");
}

TEST(test, testParse_noFormatter)
{
    ASSERT_EQ(datetime(2010, 6, 30, 1, 20), datetime::parse("yyyy-MM-ddTHH:mm", "2010-06-30T01:20"));
    ASSERT_EQ(datetime(2010, 1, 2, 14, 50, 30), datetime::parse("yyyy--ddTHH:mm:ss", "2010--02T14:50:30"));
}

TEST(test, testParse_noFormatter2)
{
    ASSERT_EQ(datetime(2010, 6, 30, 1, 20), datetime::parse("yyyy-MM-ddTHH:mm", "2010-06-30T01:20"));
    ASSERT_EQ(datetime(2010, 1, 2, 14, 50), datetime::parse("yyyy--ddTHH:mm:ss", "2010--02T14:50"));
}

TEST(test, testParse_formatter2)
{
    datetime test = datetime(2010, 6, 30, 13, 0, 0);
    ASSERT_EQ(test.to_string("yyyy--dd MM HH"), "2010--30 06 13");
}

TEST(test, testParse_noFormatter_vs_constructor_noOffset)
{
    datetime parsed = datetime::parse("yyyy-MM-ddTHH:mm", "2010-06-30T01:20");
    datetime constructed = datetime(2010, 6, 30, 1, 20);
    ASSERT_EQ(constructed, parsed);
}

TEST(test, testParse_noFormatter_vs_constructor_correctOffset)
{
    datetime parsed = datetime::parse("yyyy-MM-ddTHH:mm", "2010-06-30T01:20+01:00");
    datetime constructed = datetime(2010, 6, 30, 1, 20);
    ASSERT_EQ(constructed, parsed);
}

TEST(test, testAdd_DurationFieldType_int_dstOverlapWinter_addZero)
{
    datetime test = datetime(2011, 10, 30, 2, 30, 0);
    test.add_hours(1);
    ASSERT_EQ("2011-10-30 03:30:00", test.to_string());
}

TEST(test, testAddYears_int1)
{
    datetime test = datetime(2002, 6, 9, 5, 6, 7);
    test.add_years(8);
    ASSERT_EQ("2010-06-09 05:06:07", test.to_string());
}

TEST(test, testAddYears_int_dstOverlapSummer_addZero)
{
    datetime test = datetime(2011, 10, 30, 2, 30, 0);
    ASSERT_EQ("2011-10-30 02:30:00", test.to_string());
    test.add_years(0);
    ASSERT_EQ("2011-10-30 02:30:00", test.to_string());
}

TEST(test, testAddYears_int_dstOverlapWinter_addZero)
{
    datetime test = datetime(2011, 10, 30, 2, 30, 0);
    test.add_hours(1);
    ASSERT_EQ("2011-10-30 03:30:00", test.to_string());
    test.add_years(0);
    ASSERT_EQ("2011-10-30 03:30:00", test.to_string());
}

TEST(test, testAddMonths_int1)
{
    datetime test = datetime(2002, 6, 9, 5, 6, 7);
    test.add_months(6);
    ASSERT_EQ("2002-12-09 05:06:07", test.to_string());
}

TEST(test, testAddMonths_int_dstOverlapSummer_addZero)
{
    datetime test = datetime(2011, 10, 30, 2, 30, 0);
    ASSERT_EQ("2011-10-30 02:30:00", test.to_string());
    test.add_months(0);
    ASSERT_EQ("2011-10-30 02:30:00", test.to_string());
}

TEST(test, testAddDays_int1)
{
    datetime test = datetime(2002, 6, 9, 5, 6, 7);
    test.add_days(17);
    ASSERT_EQ("2002-06-26 05:06:07", test.to_string());
}

TEST(test, testAddMonths_int_dstOverlapWinter_addZero)
{
    datetime test = datetime(2011, 10, 30, 2, 30, 0);
    test.add_hours(1);
    ASSERT_EQ("2011-10-30 03:30:00", test.to_string());
    test.add_months(0);
    ASSERT_EQ("2011-10-30 03:30:00", test.to_string());
}

TEST(test, testAddDays_int_dstOverlapSummer_addZero)
{
    datetime test = datetime(2011, 10, 30, 2, 30, 0);
    ASSERT_EQ("2011-10-30 02:30:00", test.to_string());
    test.add_days(0);
    ASSERT_EQ("2011-10-30 02:30:00", test.to_string());
}

TEST(test, testAddDays_int_dstOverlapWinter_addZero)
{
    datetime test = datetime(2011, 10, 30, 2, 30, 0);
    test.add_hours(1);
    ASSERT_EQ("2011-10-30 03:30:00", test.to_string());
    test.add_days(0);
    ASSERT_EQ("2011-10-30 03:30:00", test.to_string());
}

TEST(test, testAddHours_int1)
{
    datetime test = datetime(2002, 6, 9, 5, 6, 7);
    test.add_hours(13);
    ASSERT_EQ("2002-06-09 18:06:07", test.to_string());
}

TEST(test, testAddHours_int_dstOverlapSummer_addZero)
{
    datetime test = datetime(2011, 10, 30, 2, 30, 0);
    ASSERT_EQ("2011-10-30 02:30:00", test.to_string());
    test.add_hours(0);
    ASSERT_EQ("2011-10-30 02:30:00", test.to_string());
}

TEST(test, testAddHours_int_dstOverlapWinter_addZero)
{
    datetime test = datetime(2011, 10, 30, 2, 30, 0);
    test.add_hours(1);
    ASSERT_EQ("2011-10-30 03:30:00", test.to_string());
    test.add_hours(0);
    ASSERT_EQ("2011-10-30 03:30:00", test.to_string());
}

TEST(test, testAddMinutes_int1)
{
    datetime test = datetime(2002, 6, 9, 5, 6, 7);
    test.add_minutes(13);
    ASSERT_EQ("2002-06-09 05:19:07", test.to_string());
}

TEST(test, testAddMinutes_int_dstOverlapSummer_addZero)
{
    datetime test = datetime(2011, 10, 30, 2, 30, 0);
    ASSERT_EQ("2011-10-30 02:30:00", test.to_string());
    test.add_minutes(0);
    ASSERT_EQ("2011-10-30 02:30:00", test.to_string());
}

TEST(test, testAddMinutes_int_dstOverlapWinter_addZero)
{
    datetime test = datetime(2011, 10, 30, 2, 30, 0);
    test.add_hours(1);
    ASSERT_EQ("2011-10-30 03:30:00", test.to_string());
    test.add_minutes(0);
    ASSERT_EQ("2011-10-30 03:30:00", test.to_string());
}

TEST(test, testAddSeconds_int1)
{
    datetime test = datetime(2002, 6, 9, 5, 6, 7);
    test.add_seconds(13);
    ASSERT_EQ("2002-06-09 05:06:20", test.to_string());
}

TEST(test, testAddSeconds_int_dstOverlapSummer_addZero)
{
    datetime test = datetime(2011, 10, 30, 2, 30, 0);
    ASSERT_EQ("2011-10-30 02:30:00", test.to_string());
    test.add_seconds(0);
    ASSERT_EQ("2011-10-30 02:30:00", test.to_string());
}

TEST(test, testAddSeconds_int_dstOverlapWinter_addZero)
{
    datetime test = datetime(2011, 10, 30, 2, 30, 0);
     test.add_hours(1);
    ASSERT_EQ("2011-10-30 03:30:00", test.to_string());
    test.add_seconds(0);
    ASSERT_EQ("2011-10-30 03:30:00", test.to_string());
}


GTEST_API_ int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
