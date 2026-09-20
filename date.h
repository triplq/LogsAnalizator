#pragma once

#include <stdexcept>
#include <string>
#include <ctime>

class Date {
private:
	unsigned int year;
	unsigned int month;
	unsigned int day;

public:
	explicit Date(const std::string& date) {
		if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
			throw std::invalid_argument("Wrong data type");
		}

		year = std::stoi(date.substr(0, 4));
		month = std::stoi(date.substr(5, 2));
		day = std::stoi(date.substr(8, 2));
	}

	bool is_current() const {
		std::time_t now = std::time(nullptr);
		std::tm *now_tm = std::localtime(&now);

		return !(year != now_tm->tm_year + 1900 || month != now_tm->tm_mon + 1 || day != now_tm->tm_mday);
	}

	unsigned int get_year() const { return year; }
	unsigned int get_month() const { return month; }
	unsigned int get_day() const { return day; };
};