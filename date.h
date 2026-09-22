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
	Date() { }
	explicit Date(std::string_view date) {
		if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
			throw std::invalid_argument("Wrong data type");
		}

		std::string date_string(date.substr(0, 4));
		year = std::stoi(date_string);

		date_string = date.substr(5, 2);
		month = std::stoi(date_string);

		date_string = date.substr(8, 2);
		day = std::stoi(date_string);
	}

	bool is_current() const {
		std::time_t now = std::time(nullptr);
		std::tm *now_tm = std::localtime(&now);

		return !(year != now_tm->tm_year + 1900 || month != now_tm->tm_mon + 1 || day != now_tm->tm_mday);
	}


	bool operator> (const Date& other) const {
		return year > other.year || year >= other.year && month > other.month || year >= other.year && month >= other.month && day > other.day;
	}

	bool operator< (const Date& other) const {
		return year < other.year || year <= other.year && month < other.month || year <= other.year && month <= other.month && day < other.day;
	}

	bool operator== (const Date& other) const {
		return day == other.day && month == other.month && year == other.year;
	}

	bool operator!= (const Date& other) const {
		return day != other.day || month != other.month || year != other.year;
	}

	bool operator>= (const Date& other) const {
		return year > other.year || year >= other.year && month > other.month || year >= other.year && month >= other.month && day > other.day || day == other.day && month == other.month && year == other.year;
	}

	bool operator<= (const Date& other) const {
		return year < other.year || year <= other.year && month < other.month || year <= other.year && month <= other.month && day < other.day || day == other.day && month == other.month && year == other.year;
	}

	unsigned int get_year() const { return year; }
	unsigned int get_month() const { return month; }
	unsigned int get_day() const { return day; };
};