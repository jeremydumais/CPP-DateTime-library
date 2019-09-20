#include "../../src/datetime.h"
#include <iostream>
#include <assert.h>
#include <cstring>
#include <exception>

using namespace std;
using namespace jed_utils;

void test_timespan_constructor()
{
	// Invalid hour (under)
	try { timespan tsTest(0, -24, 0, 0); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "hours must be between 0 and 23") == 0);
	}
	// Invalid hour (over)
	try { timespan tsTest(0, 24, 0, 0); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "hours must be between 0 and 23") == 0);
	}
	// Invalid minute (under)
	try { timespan tsTest(0, 0, -60, 0); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "minutes must be between 0 and 59") == 0);
	}
	// Invalid minute (over)
	try { timespan tsTest(0, 0, 60, 0); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "minutes must be between 0 and 59") == 0);
	}
	// Invalid second (under)
	try { timespan tsTest(0, 0, 0, -60); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "seconds must be between 0 and 59") == 0);
	}
	// Invalid second (over)
	try { timespan tsTest(0, 0, 0, 60); }
	catch (const std::invalid_argument &e) {
		assert(strcmp(e.what(), "seconds must be between 0 and 59") == 0);
	}
}

void test_timespan_get_total_seconds()
{
	timespan ts(0, 0, 0, 15);
	assert(ts.get_total_seconds() == 15);
	ts = timespan(0, 0, 3, 15);
	assert(ts.get_total_seconds() == 195);
	ts = timespan(0, 1, 3, 15);
	assert(ts.get_total_seconds() == 3795);
	ts = timespan(1, 1, 3, 15);
	assert(ts.get_total_seconds() == 90195);
	//Negative values
	ts = timespan(0, 0, 0, -15);
	assert(ts.get_total_seconds() == -15);
	ts = timespan(0, 0, -3, -15);
	assert(ts.get_total_seconds() == -195);
	ts = timespan(0, -1, -3, -15);
	assert(ts.get_total_seconds() == -3795);
	ts = timespan(-1, -1, -3, -15);
	assert(ts.get_total_seconds() == -90195);

}

void test_timespan_get_total_minutes()
{
	timespan ts(0, 0, 0, 15);
	assert(ts.get_total_minutes() == 0);
	ts = timespan(0, 0, 3, 15);
	assert(ts.get_total_minutes() == 3);
	ts = timespan(0, 1, 3, 15);
	assert(ts.get_total_minutes() == 63);
	ts = timespan(1, 1, 3, 15);
	assert(ts.get_total_minutes() == 1503);
	//Negative values
	ts = timespan(0, 0, 0, -15);
	assert(ts.get_total_minutes() == 0);
	ts = timespan(0, 0, -3, -15);
	assert(ts.get_total_minutes() == -3);
	ts = timespan(0, -1, -3, -15);
	assert(ts.get_total_minutes() == -63);
	ts = timespan(-1, -1, -3, -15);
	assert(ts.get_total_minutes() == -1503);
}

void test_timespan_get_total_hours()
{
	timespan ts(0, 0, 0, 15);
	assert(ts.get_total_hours() == 0);
	ts = timespan(0, 0, 3, 15);
	assert(ts.get_total_hours() == 0);
	ts = timespan(0, 1, 3, 15);
	assert(ts.get_total_hours() == 1);
	ts = timespan(3, 1, 3, 15);
	assert(ts.get_total_hours() == 73);
	//Negative values
	ts = timespan(0, 0, 0, -15);
	assert(ts.get_total_hours() == 0);
	ts = timespan(0, 0, -3, -15);
	assert(ts.get_total_hours() == 0);
	ts = timespan(0, -1, -3, -15);
	assert(ts.get_total_hours() == -1);
	ts = timespan(-3, -1, -3, -15);
	assert(ts.get_total_hours() == -73);
}

void test_timespan_operator_less()
{
	timespan ts1(3, 2, 1, 0);
	timespan ts2(3, 2, 0, 0);
	assert(ts2 < ts1);
	ts1 = timespan(3, 2, 1, 1);
	ts2 = timespan(-3, -2, -1, -1);
	assert(ts2 < ts1);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(4, 3, 2, 0);
	assert(ts2 < ts1);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(4, 3, 1, 1);
	assert(ts2 < ts1);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(4, 2, 2, 1);
	assert(ts2 < ts1);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(3, 3, 2, 1);
	assert(ts2 < ts1);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(3, 5, 4, 6);
	assert(ts2 < ts1);
}

void test_timespan_operator_less_equal()
{
	timespan ts1(3, 2, 1, 0);
	timespan ts2(3, 2, 0, 0);
	assert(ts2 <= ts1);
	ts1 = timespan(3, 2, 1, 1);
	ts2 = timespan(-3, -2, -1, -1);
	assert(ts2 <= ts1);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(4, 3, 2, 0);
	assert(ts2 <= ts1);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(4, 3, 1, 1);
	assert(ts2 <= ts1);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(4, 2, 2, 1);
	assert(ts2 <= ts1);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(3, 3, 2, 1);
	assert(ts2 <= ts1);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(3, 5, 4, 6);
	assert(ts2 <= ts1);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(4, 3, 2, 1);
	assert(ts2 <= ts1);
	ts1 = timespan(-4, -3, -2, -1);
	ts2 = timespan(-4, -3, -2, -1);
	assert(ts2 <= ts1);
	ts1 = timespan(0, 0, 0, 0);
	ts2 = timespan(0, 0, 0, 0);
	assert(ts2 <= ts1);
}

void test_timespan_operator_greater()
{
	timespan ts1(3, 2, 1, 0);
	timespan ts2(3, 2, 0, 0);
	assert(ts1 > ts2);
	ts1 = timespan(3, 2, 1, 1);
	ts2 = timespan(-3, -2, -1, -1);
	assert(ts1 > ts2);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(4, 3, 2, 0);
	assert(ts1 > ts2);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(4, 3, 1, 1);
	assert(ts1 > ts2);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(4, 2, 2, 1);
	assert(ts1 > ts2);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(3, 3, 2, 1);
	assert(ts1 > ts2);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(3, 5, 4, 6);
	assert(ts1 > ts2);
}

void test_timespan_operator_greater_equal()
{
	timespan ts1(3, 2, 1, 0);
	timespan ts2(3, 2, 0, 0);
	assert(ts1 >= ts2);
	ts1 = timespan(3, 2, 1, 1);
	ts2 = timespan(-3, -2, -1, -1);
	assert(ts1 >= ts2);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(4, 3, 2, 0);
	assert(ts1 >= ts2);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(4, 3, 1, 1);
	assert(ts1 >= ts2);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(4, 2, 2, 1);
	assert(ts1 >= ts2);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(3, 3, 2, 1);
	assert(ts1 >= ts2);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(3, 5, 4, 6);
	assert(ts1 >= ts2);
	ts1 = timespan(4, 3, 2, 1);
	ts2 = timespan(4, 3, 2, 1);
	assert(ts2 >= ts1);
	ts1 = timespan(-4, -3, -2, -1);
	ts2 = timespan(-4, -3, -2, -1);
	assert(ts2 >= ts1);
	ts1 = timespan(0, 0, 0, 0);
	ts2 = timespan(0, 0, 0, 0);
	assert(ts2 >= ts1);
}

void test_timespan_operator_equal()
{
	assert(timespan(1, 2, 3, 4) == timespan(1, 2, 3, 4));
	assert(timespan(-1, -2, -3, -4) == timespan(-1, -2, -3, -4));
	assert(!(timespan(1, 2, 3, 4) == timespan(1, 2, 3, 3)));
	assert(!(timespan(1, 2, 3, 4) == timespan(1, 2, 2, 4)));
	assert(!(timespan(1, 2, 3, 4) == timespan(1, 1, 3, 4)));
	assert(!(timespan(1, 2, 3, 4) == timespan(0, 2, 3, 4)));
}

void test_timespan_operator_not_equal()
{
	assert(!(timespan(1, 2, 3, 4) != timespan(1, 2, 3, 4)));
	assert(!(timespan(-1, -2, -3, -4) != timespan(-1, -2, -3, -4)));
	assert(timespan(1, 2, 3, 4) != timespan(1, 2, 3, 3));
	assert(timespan(1, 2, 3, 4) != timespan(1, 2, 2, 4));
	assert(timespan(1, 2, 3, 4) != timespan(1, 1, 3, 4));
	assert(timespan(1, 2, 3, 4) != timespan(0, 2, 3, 4));
}