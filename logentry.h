#pragma once

#include <string>
#include "time.h"
#include "date.h"
#include "level.h"

struct LogEntry {
	Date date;
	Time time;
	Level level;
	std::string system;
	std::string message;

	explicit LogEntry(std::string_view str);
};