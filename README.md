# Jed# C++ DateTime Library

## Jed# C++ DateTime library is a simple Date and time library built in C++.

### How to build the DateTime library or integrate it in your application

Follow this [link](https://github.com/jeremydumais/CPP-DateTime-library/wiki/How-to-build-the-DateTime-library-or-integrate-it-in-your-application) for a quick guide on how to build the DateTime library or integrate it in your application.

### Some examples

##### Get the current date and time

```c++
datetime dtTest = datetime();
```

##### Create a date

```c++
datetime dtTest = datetime(2016, 11, 25);
```

##### Create a date with time (year, month, day, hour, minute, second)

```c++
datetime dtTest = datetime(2016, 11, 25, 20, 12, 44);
```

##### Create a date with time (12 hour format) (year, month, day, hour, minute, second, period)

```c++
datetime dtTest = datetime(2016, 11, 25, 4, 12, 44, period::PM);
```

##### Add a week to a date

```c++
datetime dtTest = datetime(2016, 11, 25, 20, 12, 44);
dtTest.add_days(7);
```

##### Substract a week from a date

```c++
datetime dtTest = datetime(2016, 11, 25, 20, 12, 44);
dtTest.add_days(-7);
```

##### Display the date in standard form (yyyy-MM-dd HH:mm:ss)

```c++
datetime dtTest = datetime();
cout << dtTest.to_string() << endl;
```

##### Display the date in custom format ("yyyy-MM-dd hh:mm:ss tt")

```c++
datetime dtTest = datetime();
cout << dtTest.to_string("yyyy-MM-dd hh:mm:ss tt") << endl;
```

##### Get weekday of a datetime

```c++
//enum weekday { sunday, monday, tuesday, wednesday, thursday, friday, saturday };
datetime dtTest = datetime(2015, 02, 14, 11, 11, 11);
assert(dtTest.get_weekday() == weekday::saturday);
```

##### Parse a string to a datetime

```c++
datetime dtTest = datetime::parse(string("yyyy/MM/dd HH:mm:ss"), string("2016-08-18 23:14:42"));
```

##### Substracting two datetime objetcs (Example 1)

```c++
datetime date1(2016, 12, 31, 11, 32, 5);
datetime date2(2016, 12, 25, 13, 55, 12);
timespan ts1 = date2 - date1;
assert(ts1.get_days() == -5);
assert(ts1.get_hours() == -21);
assert(ts1.get_minutes() == -36);
assert(ts1.get_seconds() == -53);
```

##### Substracting two datetime objetcs (Example 2)

```c++
datetime date1(2016, 11, 25);
datetime date2(2016, 12, 5);
timespan ts1 = date2 - date1;
assert(ts1.get_days() == 10);
assert(ts1.get_hours() == 0);
assert(ts1.get_minutes() == 0);
assert(ts1.get_seconds() == 0);
```

##### Get total minutes of a timespan

```c++
timespan ts(0, 1, 3, 15);
assert(ts.get_total_minutes() == 63);
```

### datetime class

#### Constructors
```c++
datetime(); // Get the current date and time
datetime(int year, 
	int month, 
	int day, 
	int hour = 0, 
	int minute = 0, 
	int second = 0, 
	period day_period = period::undefined);
```

#### Available methods
```c++
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
//NB: At this time only the following format specifiers (yyyy, MM, dd, HH, hh, mm, ss and tt) 
//    are supported by the parse method.
static bool is_leapyear(int year);
```	

#### Supported operators

| Operator | Quick description | Example |
| --- | --- | --- |
| <<  | Output stream operator | datetime dtTest = datetime();<br>cout << dtTest << endl; |
| < | Less operator | datetime dtTest = datetime(2015, 02, 14, 14, 00, 00);<br>datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 01);<br>assert(dtTest < dtTest2); |
| <= | Less equal operator | datetime dtTest = datetime(2015, 02, 14, 14, 00, 00);<br>datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 01);<br>assert(dtTest <= dtTest2); |
| > | Greater operator | datetime dtTest = datetime(2015, 02, 14, 14, 00, 01);<br>datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 00);<br>assert(dtTest > dtTest2); |
| >= | Greater equal operator | datetime dtTest = datetime(2015, 02, 14, 14, 00, 01);<br>datetime dtTest2 = datetime(2015, 02, 14, 14, 00, 00);<br>assert(dtTest >= dtTest2); |
| == | Equality operator | assert(datetime(2017, 1, 8, 15, 28, 23) == datetime(2017, 1, 8, 15, 28, 23)); |
| != | Inequality operator | assert(datetime(2017, 1, 8, 15, 28, 23) != datetime(2017, 1, 8, 15, 28, 22)); |
| - | Minus operator | datetime dtTest = datetime(2015, 02, 11, 13, 00, 00);<br>datetime dtTest2 = datetime(2015, 02, 14, 15, 00, 00);<br>timespan tsTest = dtTest2 - dtTest;<br>assert(tsTest.get_days() == 3);<br>assert(tsTest.get_hours() == 2); |
	
#### Custom Date and Time Format Strings

| Format specifier | Description |
| --- | --- |
| yyyy | The year as a four-digit number. |
| yy | The year as a two-digit number. |
| M | The month, from 1 through 12. |
| MM | The month, from 01 through 12. |
| d | The day of the month, from 1 through 31. |
| dd | The day of the month, from 01 through 31. |
| h | The hour, using a 12-hour clock from 1 to 12. |
| hh | The hour, using a 12-hour clock from 01 to 12. |
| H | The hour, using a 24-hour clock from 0 to 23. |
| HH | The hour, using a 24-hour clock from 00 to 23. |
| m | The minute, from 0 through 59. |
| mm | The minute, from 00 through 59. |
| s | The second, from 0 through 59. |
| ss | The second, from 00 through 59. |
| tt | The period (AM/PM designator). |

#### Enumerators
```c++
enum weekday { sunday, monday, tuesday, wednesday, thursday, friday, saturday };
enum period { undefined, AM, PM };  //undefined is for 24 hour format
```

### timespan class

#### Constructor
```c++
timespan(int days, int hours=0, int minutes=0, int seconds=0);
```

#### Available methods
```c++
int get_days();
int get_hours();
int get_minutes();
int get_seconds();
int get_total_hours();
int get_total_minutes();
int get_total_seconds();
```	

#### Supported operators

| Operator | Quick description | Example |
| --- | --- | --- |
| < | Less operator | timespan ts1(3, 2, 1, 0);<br>timespan ts2(3, 2, 0, 0);<br>assert(ts2 < ts1); |
| <= | Less equal operator | assert(ts2 <= ts1);<br>ts1 = timespan(4, 3, 2, 1);<br>ts2 = timespan(4, 3, 2, 1); |
| > | Greater operator | timespan ts1(3, 2, 1, 0);<br>timespan ts2(3, 2, 0, 0);<br>assert(ts1 > ts2); |
| >= | Greater equal operator | ts1 = timespan(4, 3, 2, 1);<br>ts2 = timespan(4, 3, 2, 1);<br>assert(ts2 >= ts1); |
| == | Equality operator | assert(timespan(1, 2, 3, 4) == timespan(1, 2, 3, 4)); |
| != | Inequality operator | assert(timespan(1, 2, 3, 4) != timespan(1, 2, 3, 3)); |

