#include "logentry.h"
#include <cctype>
#include <stdexcept>
#include <vector>
#include <iostream>

LogEntry::LogEntry(std::string_view str) {
	std::vector<std::string_view> words;

	auto start = str.find_first_not_of(" ");
	while (start != std::string::npos) {
		auto end = str.find_first_of(" ", start);

		words.push_back(str.substr(start, end-start));
		start = str.find_first_not_of(" ", end);
	}

	if (words.size() < 5) {
		throw std::invalid_argument("Low quantity of words");
	}

	date = Date(words[0]);
	time = Time(words[1]);

	if (words[2] == "ERROR") {
		level = Level::Error;
	} else if (words[2] == "WARN") {
		level = Level::Warn;
	} else if (words[2] == "INFO") {
		level = Level::Info;
	} else {
		throw std::invalid_argument("Wrong level");
	}

	subsystem = words[3];
	for (auto& c : subsystem) {
		if (std::isupper(c)) {
			throw std::invalid_argument("Something with subsystem");
		}
	}

	message = words[4];

	if (!std::isupper(words[4][0])) {
		throw std::invalid_argument("Something with subsystem or message");
	}

	for (size_t i = 5; i < words.size(); i++) {
		message += " ";
		message += words[i];
	}
}

bool LogEntry::operator!= (const LogEntry& other) const {
	return (message != other.message || subsystem != other.subsystem || level != other.level || time != other.time || date != other.date);
}

std::ostream& operator<<(std::ostream& stream, const LogEntry& log) {
	std::string level;
	switch (log.level) {
	case(Level::Error):
		level = "ERROR";
		break;
	case(Level::Warn):
		level = "WARN";
		break;
	case(Level::Info):
		level = "INFO";
		break;	
	}

	stream << log.date.get_year() << '-' << log.date.get_month() << '-' << log.date.get_day() 
		<< ' ' << log.time.get_hours() << ':' << log.time.get_minutes() << ':' << log.time.get_seconds() << ' ' << level << ' '
		<< log.subsystem << ' ' << log.message;

	return stream;
}