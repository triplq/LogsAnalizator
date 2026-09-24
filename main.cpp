#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include "logentry.h"
#include "stats.h"

int main(int argc, char* argv[]) {
	std::vector<std::function<bool(const LogEntry&)>> filters;
	for (size_t i = 1; i < argc; i++) {
		std::string arg = argv[i];
		
		if (arg.find("--") != 0) {
			continue;
		}

		auto pos = arg.find("=");
		if (pos == std::string::npos) {
			continue;
		}

		std::string key = arg.substr(2, pos - 2);
		std::string value = arg.substr(pos + 1);

		if (key == "level") {
			if (value != "ERROR" && value != "WARN" && value != "INFO") {
				throw std::invalid_argument("Incorrect --level=flag");
			}
			else {
				filters.push_back([value](const LogEntry& p){
					if (value == "ERROR")
						return p.level == Level::Error;
					if (value == "INFO") 
						return p.level == Level::Info;
					if (value == "WARN")
						return p.level == Level::Warn;
				});
			}
		}

		if (key == "subsystem") {
			filters.push_back([value](const LogEntry& p){
				return p.subsystem == value;
			});
		}

		if (key == "after") {
			filters.push_back([value](const LogEntry& p){
				return p.time.get_int() > (std::stoi(value.substr(0, 2)) * 60 * 60) + (std::stoi(value.substr(3, 2)) * 60);
			});
		}

		if (key == "contains") {
			filters.push_back([value](const LogEntry& p){
				return p.message.find(value) != std::string::npos;
			});
		}
	}

	std::vector<LogEntry> logs;
	size_t counter = 0;
	std::unordered_map<Level, size_t> levels;
	std::unordered_map<std::string, size_t> subsystems;
	std::unordered_map<std::string, size_t> messages;

	std::string line;

	std::ifstream in;
	in.open("Resources/log.txt");
	if (in.is_open()) {
		while (std::getline(in, line)) {
			try {
				logs.push_back(LogEntry(line));
				if (filters.size() != 0) {
					bool allow = true;
					for (const auto& filter : filters) {
						if (!filter(logs[logs.size()-1])) {
							allow = false;
						}
					}
					if (allow) {
						std::cout << logs[logs.size()-1] << '\n';
					}
				}
				levels[logs[logs.size()-1].level]++;

				subsystems[logs[logs.size()-1].subsystem]++;

				std::string str = logs[logs.size()-1].message;
				str.erase(std::remove_if(str.begin(), str.end(), [](const unsigned char& ch) { return std::isdigit(ch); }), str.end());
				messages[str]++;
			} catch (std::invalid_argument) {
				counter++;
			}
		}
	}
	in.close();

	std::vector<std::pair<std::string, size_t>> subsystems_vector {std::make_move_iterator(subsystems.begin()), std::make_move_iterator(subsystems.end())};
	std::partial_sort(subsystems_vector.begin(), subsystems_vector.begin() + 5, subsystems_vector.end(), [](const auto& a, const auto& b){ return a.second > b.second; });
	subsystems_vector.resize(5);
	subsystems_vector.shrink_to_fit();

	std::cout << "\n=========GARBAGE LINES========\n";
	std::cout << counter << '\n';

	std::cout << "\n=========QUANTITY OF EACH LEVEL========\n";
	for (const auto& [key, val] : levels) {
		switch (key) {
		case (Level::Error) : 
			std::cout << "Errors: " << val << '\n';
			break;
		case (Level::Info) : 
			std::cout << "Infos: " << val << '\n';
			break;
		case (Level::Warn) : 
			std::cout << "Warns: " << val << '\n';
			break;
		}
	}

	std::cout << "\n=========TOP 5 NOISY SUBSYSTEMS========\n";

	for (const auto& [key, val] : subsystems_vector) {
		std::cout << key << ' ' << val << '\n';
	}

	newest_line(logs);
	oldest_line(logs);
	
	interval_between_errors(logs, levels);
	most_send_message(messages);
	

	
	return 0;
}