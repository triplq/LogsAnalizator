#pragma once

#include <string>
#include "times.hpp"
#include "date.hpp"
#include "level.hpp"

struct LogEntry {
	Date date;
	Time time;
	Level level;
	std::string subsystem;
	std::string message;

	explicit LogEntry(std::string_view str);

	bool operator!= (const LogEntry& other) const;
};

std::ostream& operator<<(std::ostream& stream, const LogEntry& log);