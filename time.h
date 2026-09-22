#pragma once

#include <stdexcept>
#include <string>
#include <ctime>

class Time {
private:
	unsigned int hours;
	unsigned int minutes;
	unsigned int seconds;

public:
	Time() { }
	explicit Time(std::string_view time) {
		if (time.length() != 8 || time[2] != ':' || time[5] != ':') {
			throw std::invalid_argument("Wrong time type");
		}

		std::string time_string(time.substr(0, 2));
		hours = std::stoi(time_string);

		time_string = time.substr(3, 2);
		minutes = std::stoi(time_string);

		time_string = time.substr(6, 2);
		seconds = std::stoi(time_string);
	}

	bool is_current() const {
		std::time_t now = std::time(nullptr);
		std::tm *now_tm = std::localtime(&now);

		return !(hours != now_tm->tm_hour || minutes != now_tm->tm_min || seconds != now_tm->tm_sec);
	}

	unsigned int get_hours() const { return hours; }
	unsigned int get_minutes() const { return minutes; }
	unsigned int get_seconds() const { return seconds; }
};