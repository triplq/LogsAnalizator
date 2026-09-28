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

		std::time_t now = std::time(nullptr);
		std::tm *now_tm = std::localtime(&now);

		std::string date_string(date.substr(0, 4));
		year = std::stoi(date_string);

		if (year > static_cast<unsigned int>(now_tm->tm_year)) 
			throw std::invalid_argument("Wrong year");

		date_string = date.substr(5, 2);
		month = std::stoi(date_string);

		if (month > 12)
			throw std::invalid_argument("Wrong month");

		date_string = date.substr(8, 2);
		day = std::stoi(date_string);

		if (day > 31) 
			throw std::invalid_argument("Wrong day");
	}

	bool operator> (const Date& other) const {
		return year > other.year || (year >= other.year && month > other.month) || (year >= other.year && month >= other.month && day > other.day);
	}

	bool operator< (const Date& other) const {
		return year < other.year || (year <= other.year && month < other.month) || (year <= other.year && month <= other.month && day < other.day);
	}

	bool operator== (const Date& other) const {
		return day == other.day && month == other.month && year == other.year;
	}

	bool operator!= (const Date& other) const {
		return day != other.day || month != other.month || year != other.year;
	}

	bool operator>= (const Date& other) const {
		return year > other.year || (year >= other.year && month > other.month) || (year >= other.year && month >= other.month && day > other.day) || (day == other.day && month == other.month && year == other.year);
	}

	bool operator<= (const Date& other) const {
		return year < other.year || (year <= other.year && month < other.month) || (year <= other.year && month <= other.month && day < other.day) || (day == other.day && month == other.month && year == other.year);
	}

	unsigned int get_year() const { return year; }
	unsigned int get_month() const { return month; }
	unsigned int get_day() const { return day; };
};