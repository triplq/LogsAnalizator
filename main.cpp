#include <iostream>
#include "time.h"
#include "date.h"

int main() {
	Date date("2026-09-20");
	Time time("20:36:40");
	std::cout << date.get_year() << ' ' << date.get_month() << ' ' << date.get_day() << '\n'; 
	std::cout << time.get_hours() << ' ' << time.get_minutes() << ' ' << time.get_seconds() << '\n';

	std::cout << date.is_current() << ' ' << time.is_current() << '\n';

	return 0;
}