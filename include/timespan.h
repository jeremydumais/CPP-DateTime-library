#ifndef TIMESPAN_H
#define TIMESPAN_H

class __declspec(dllexport) timespan
{
	public:
		timespan(int days, int hours=0, int minutes=0, int seconds=0);
		int get_days() const;
		int get_hours() const;
		int get_minutes() const;
		int get_seconds() const;
		int get_total_hours() const;
		int get_total_minutes() const;
		int get_total_seconds() const;
		//Operators
		__declspec(dllexport) friend bool operator<(const timespan &mts, const timespan &ots);
		__declspec(dllexport) friend bool operator>(const timespan &mts, const timespan &ots);
		__declspec(dllexport) friend bool operator<=(const timespan &mts, const timespan &ots);
		__declspec(dllexport) friend bool operator>=(const timespan &mts, const timespan &ots);
		__declspec(dllexport) friend bool operator==(const timespan &mts, const timespan &ots);
		__declspec(dllexport) friend bool operator!=(const timespan &mts, const timespan &ots);
	private:
		int days;
		int hours;
		int minutes;
		int seconds;
};

#endif // TIMESPAN_H