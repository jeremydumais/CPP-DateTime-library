#include <iostream>
#include <assert.h>
#include <cstring>
#include <exception>
#include <iostream>

void datetime_unittest();
void timespan_unittest();

using namespace std;

int main()
{
	// Unit tests
	datetime_unittest();
	timespan_unittest();

	cout << "Unit tests successful!" << endl;

	return 0;
}
