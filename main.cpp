#include <iostream>
#include <assert.h>
#include "include/datetime.h"
#include <cstring>

using namespace std;

void test_constructor()
{
    datetime* dtTest = new datetime(2015, 02, 14);
    assert(dtTest->get_year() == 2015);
    assert(dtTest->get_month() == 2);
    assert(dtTest->get_day() == 14);
    assert(dtTest->get_hour() == 0);
    assert(dtTest->get_minute() == 0);
    assert(dtTest->get_second() == 0);
    delete dtTest;

    dtTest = new datetime(2015, 02, 14, 23, 12, 11);
    assert(dtTest->get_year() == 2015);
    assert(dtTest->get_month() == 2);
    assert(dtTest->get_day() == 14);
    assert(dtTest->get_hour() == 23);
    assert(dtTest->get_minute() == 12);
    assert(dtTest->get_second() == 11);
    delete dtTest;
    // Invalid month (under)
    try { dtTest = new datetime(2015, 00, 14); }
    catch(const std::invalid_argument& e) {
        assert(strcmp(e.what(), "month must be between 1 and 12")==0);
    }
    // Invalid month (over)
    try { dtTest = new datetime(2015, 13, 14); }
    catch(const std::invalid_argument& e) {
        assert(strcmp(e.what(), "month must be between 1 and 12")==0);
    }
    // Invalid day (under)
    try { dtTest = new datetime(2015, 1, 0); }
    catch(const std::invalid_argument& e) {
        assert(strcmp(e.what(), "day is out of range")==0);
    }
    // Invalid day (over)
    int month_to_check_31[] = {1,3,5,7,8,10,12};
    for (int i : month_to_check_31)
    {
        try { dtTest = new datetime(2015, i, 32); }
        catch(const std::invalid_argument& e) {
            assert(strcmp(e.what(), "day is out of range")==0);
        }
    }

    int month_to_check_30[] = {4,6,9,11};
    for (int i : month_to_check_30)
    {
        try { dtTest = new datetime(2015, i, 31); }
        catch(const std::invalid_argument& e) {
            assert(strcmp(e.what(), "day is out of range")==0);
        }
    }

    try { dtTest = new datetime(2000, 2, 30); }
    catch(const std::invalid_argument& e) {
        assert(strcmp(e.what(), "day is out of range")==0);
    }
    dtTest = new datetime(2000, 02, 29);
    delete dtTest;

    try { dtTest = new datetime(2001, 2, 29); }
    catch(const std::invalid_argument& e) {
        assert(strcmp(e.what(), "day is out of range")==0);
    }
    dtTest = new datetime(2001, 02, 28);
    delete dtTest;

    // Invalid hour (under)
    try { dtTest = new datetime(2015, 1, 14, -1); }
    catch(const std::invalid_argument& e) {
        assert(strcmp(e.what(), "hour must be between 0 and 23")==0);
    }
    // Invalid hour (over)
    try { dtTest = new datetime(2015, 1, 14, 24); }
    catch(const std::invalid_argument& e) {
        assert(strcmp(e.what(), "hour must be between 0 and 23")==0);
    }
    // Invalid minute (under)
    try { dtTest = new datetime(2015, 1, 14, 1, -1); }
    catch(const std::invalid_argument& e) {
        assert(strcmp(e.what(), "minute must be between 0 and 59")==0);
    }
    // Invalid minute (over)
    try { dtTest = new datetime(2015, 1, 14, 1, 60); }
    catch(const std::invalid_argument& e) {
        assert(strcmp(e.what(), "minute must be between 0 and 59")==0);
    }
    // Invalid second (under)
    try { dtTest = new datetime(2015, 1, 14, 1, 1, -1); }
    catch(const std::invalid_argument& e) {
        assert(strcmp(e.what(), "second must be between 0 and 59")==0);
    }
    // Invalid second (over)
    try { dtTest = new datetime(2015, 1, 14, 1, 1, 60); }
    catch(const std::invalid_argument& e) {
        assert(strcmp(e.what(), "second must be between 0 and 59")==0);
    }
}

void test_to_string()
{
    datetime* dtTest = new datetime(2015, 02, 14);
    assert(strcmp(dtTest->to_string().c_str(), "2015-02-14 00:00:00")==0);
    delete dtTest;

    dtTest = new datetime(2015, 02, 14, 11, 7, 2);
    assert(strcmp(dtTest->to_string().c_str(), "2015-02-14 11:07:02")==0);
    delete dtTest;

    dtTest = new datetime(2015, 02, 14, 11, 55, 45);
    assert(strcmp(dtTest->to_string().c_str(), "2015-02-14 11:55:45")==0);
    delete dtTest;
}

void test_to_shortdate_string()
{
    datetime* dtTest = new datetime(2015, 02, 14);
    assert(strcmp(dtTest->to_shortdate_string().c_str(), "2015-02-14")==0);
    delete dtTest;

    dtTest = new datetime(2015, 02, 14, 11, 7, 2);
    assert(strcmp(dtTest->to_shortdate_string().c_str(), "2015-02-14")==0);
    delete dtTest;

    dtTest = new datetime(2015, 02, 14, 11, 55, 45);
    assert(strcmp(dtTest->to_shortdate_string().c_str(), "2015-02-14")==0);
    delete dtTest;
}

void test_add_days()
{
    datetime* dtTest = new datetime(2015, 02, 14);
    dtTest->add_days(2);

    assert(strcmp(dtTest->to_shortdate_string().c_str(), "2015-02-16")==0);
    delete dtTest;

    dtTest = new datetime(2015, 02, 27, 11, 7, 2);
    dtTest->add_days(5);
    assert(strcmp(dtTest->to_shortdate_string().c_str(), "2015-03-04")==0);
    delete dtTest;

    dtTest = new datetime(2015, 02, 02, 11, 7, 2);
    dtTest->add_days(-3);
    assert(strcmp(dtTest->to_shortdate_string().c_str(), "2015-01-30")==0);
    delete dtTest;
}

void test_add_months()
{
    datetime* dtTest = new datetime(2015, 02, 14);
    dtTest->add_months(2);
    assert(strcmp(dtTest->to_shortdate_string().c_str(), "2015-04-14")==0);
    delete dtTest;

    dtTest = new datetime(2015, 04, 14);
    dtTest->add_months(-2);
    assert(strcmp(dtTest->to_shortdate_string().c_str(), "2015-02-14")==0);
    delete dtTest;

    dtTest = new datetime(2015, 11, 14);
    dtTest->add_months(3);
    assert(strcmp(dtTest->to_shortdate_string().c_str(), "2016-02-14")==0);
    delete dtTest;

    dtTest = new datetime(2015, 11, 14);
    dtTest->add_months(23);
    assert(strcmp(dtTest->to_shortdate_string().c_str(), "2017-10-14")==0);
    delete dtTest;

    dtTest = new datetime(2015, 11, 14);
    dtTest->add_months(-13);
    assert(strcmp(dtTest->to_shortdate_string().c_str(), "2014-10-14")==0);
    delete dtTest;
}

void test_add_years()
{
    datetime* dtTest = new datetime(2015, 02, 14);
    dtTest->add_years(2);
    assert(strcmp(dtTest->to_shortdate_string().c_str(), "2017-02-14")==0);
    delete dtTest;

    dtTest = new datetime(2015, 02, 14);
    dtTest->add_years(-2);
    assert(strcmp(dtTest->to_shortdate_string().c_str(), "2013-02-14")==0);
    delete dtTest;
}

void test_is_leapyear()
{
    datetime* dtTest = new datetime(2000, 01, 01);
    assert(dtTest->is_leapyear());
    delete dtTest;
    dtTest = new datetime(2004, 01, 01);
    assert(dtTest->is_leapyear());
    delete dtTest;
    dtTest = new datetime(1700, 01, 01);
    assert(!dtTest->is_leapyear());
    delete dtTest;
}

int main()
{
    // Unit tests
    test_constructor();
    test_to_string();
    test_to_shortdate_string();
    test_add_days();
    test_add_months();
    test_add_years();
    test_is_leapyear();

    datetime dtTest = datetime();
    /*datetime *dtTest2 = new datetime(1982,8,18);
    datetime dtTest3(*dtTest2);
    delete dtTest2;
    cout << dtTest3.to_shortdate_string() << endl;*/
    dtTest.add_months(-22);
    cout << dtTest.to_string() << endl;
    //delete dtTest;
    //delete dtTest2;

    return 0;
}
