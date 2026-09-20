#pragma once

#include <string>
#include "time.h"
#include "date.h"

struct LogEntry {
	Date date;
	Time time;
	std::string level;
	std::string system;
	std::string message;


};