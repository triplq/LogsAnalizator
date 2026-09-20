#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include "time.h"
#include "date.h"
#include "level.h"

struct LogEntry {
	Date date;
	Time time;
	Level level;
	std::string system;
	std::string message;

	explicit LogEntry(std::string_view str) {
		std::vector<std::string_view> words;

		auto start = str.find_first_not_of(" ");
		while (start != std::string::npos) {
			auto end = str.find_first_of(" ", start);

			words.push_back(str.substr(start, end-start));
			start = str.find_first_not_of(" ", end);
		}

		if (words.size() < 5) {
			std::invalid_argument("Low quantity of words");
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

		system = words[3];
		message = words[4];

		for (size_t i = 5; i < words.size(); i++) {
			message += " ";
			message += words[i];
		}

	}
};