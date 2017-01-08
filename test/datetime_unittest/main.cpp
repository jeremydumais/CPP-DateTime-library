#include "..\..\include\datetime.h"
#include <iostream>
#include <assert.h>
#include <cstring>
#include <exception>
#include <conio.h>


void datetime_unittest();
void timespan_unittest();

int main()
{
	// Unit tests
	datetime_unittest();
	timespan_unittest();

	cout << "Unit tests successful!" << endl;

	_getch();
	return 0;
}
