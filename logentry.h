#pragma once

#include <string>
#include "time.h"
#include "date.h"
#include "level.h"

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