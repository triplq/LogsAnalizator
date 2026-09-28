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

		if (hours > 23) 
			throw std::invalid_argument("Wrong hour");

		time_string = time.substr(3, 2);
		minutes = std::stoi(time_string);

		if (minutes > 59)
			throw std::invalid_argument("Wrong minutes");

		time_string = time.substr(6, 2);
		seconds = std::stoi(time_string);

		if (seconds > 59)
			throw std::invalid_argument("Wrong seconds");
	}

	bool operator> (const Time& other) const {
		return hours > other.hours || (hours >= other.hours && minutes > other.minutes) || (hours >= other.hours && minutes >= other.minutes && seconds > other.seconds);
	}

	bool operator< (const Time& other) const {
		return hours < other.hours || (hours <= other.hours && minutes < other.minutes) || (hours <= other.hours && minutes <= other.minutes && seconds < other.seconds);
	}

	bool operator== (const Time& other) const {
		return seconds == other.seconds && minutes == other.minutes && hours == other.hours;
	}

	bool operator!= (const Time& other) const {
		return seconds != other.seconds || minutes != other.minutes || hours != other.hours;
	}

	bool operator>= (const Time& other) const {
		return hours > other.hours || (hours >= other.hours && minutes > other.minutes) || (hours >= other.hours && minutes >= other.minutes && seconds > other.seconds) || (seconds == other.seconds && minutes == other.minutes && hours == other.hours);
	}

	bool operator<= (const Time& other) const {
		return hours < other.hours || (hours <= other.hours && minutes < other.minutes) || (hours <= other.hours && minutes <= other.minutes && seconds < other.seconds) || (seconds == other.seconds && minutes == other.minutes && hours == other.hours);
	}

	unsigned int get_int() const {
		return (hours * 60 * 60) + (minutes* 60) + seconds;
	}
	unsigned int get_hours() const { return hours; }
	unsigned int get_minutes() const { return minutes; }
	unsigned int get_seconds() const { return seconds; }
};