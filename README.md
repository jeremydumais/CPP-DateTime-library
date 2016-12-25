#Jed C++ DateTime Library

###Jed C++ DateTime library is a simple Date and time library built in C++.

####Here's some examples

//Get the current date and time

	datetime dtTest = datetime();

//Create a known date

	datetime dtTest = datetime(2016, 11, 25);

//Create a known date with time (year, month, day, hour, minute, second)

	datetime dtTest = datetime(2016, 11, 25, 20, 12, 44);

//Add a week to a date

	datetime dtTest = datetime(2016, 11, 25, 20, 12, 44);
	dtTest.add_days(7);

//Substract a week from a date

	datetime dtTest = datetime(2016, 11, 25, 20, 12, 44);
	dtTest.add_days(-7);

//Display the date in standard form (yyyy-MM-dd HH:mm:ss)

	datetime dtTest = datetime();
	cout << dtTest.to_string() << endl;

//Get weekday of a datetime

    //enum weekday { sunday, monday, tuesday, wednesday, thursday, friday, saturday };
    datetime dtTest = datetime(2015, 02, 14, 11, 11, 11);
    assert(dtTest.get_weekday() == weekday::saturday);

//Parse a string to a datetime

    datetime dtTest = datetime::parse(string("yyyy/MM/dd HH:mm:ss"), string("2016-08-18 23:14:42"));


Methods available:

	string to_string();
	string to_shortdate_string();
	int get_year();
	int get_month();
	int get_day();
	int get_hour();
	int get_minute();
	int get_second();
	weekday get_weekday();
	void add_years(int nb_years);
	void add_months(int nb_months);
	void add_days(int nb_days);
	void add_hours(int nb_hours);
	void add_minutes(int nb_minutes);
	void add_seconds(int nb_seconds);
	bool is_leapyear();
	static datetime parse(string format, string value);

