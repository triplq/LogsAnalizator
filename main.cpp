#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include "logentry.h"

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
			if (value != "ERROR" || value != "WARN" || value != "INFO") {
				throw std::invalid_argument("Incorrect --level=flag");
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
				return p.message.find(value);
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


	std::cout << "\n=========THE OLDEST LINE========\n";
	auto it_old = std::max_element(logs.begin(), logs.end(), [](const auto& a, const auto& b){ return a.time > b.time && a.date >= b.date; });
	std::cout << *it_old << '\n';

	std::cout << "\n=========THE NEWEST LINE========\n";
	auto it_new = std::max_element(logs.begin(), logs.end(), [](const auto& a, const auto& b){ return a.time < b.time && a.date <= b.date; });
	std::cout << *it_new << '\n';


	// std::cout << "\n=========ALL LOGS AT X HOUR========\n";
	// int hour;
	// std::cout << "ENTER AN HOUR: ";
	// std::cin >> hour;

	// auto it_hour = logs.begin();
	// while ((it_hour = std::find_if(it_hour, logs.end(), [&](const auto& a){ return a.time.get_hours() == hour; })) != logs.end()) {
	// 	std::cout << *it_hour << '\n';
	// 	it_hour++;
	// }


	std::cout << "\n=========AVERAGE INTERVAL BETWEEN ERRORS========\n";
	auto it_prev = *std::find_if(logs.begin(), logs.end(), [](const auto& a) { return (a.level == Level::Error); });

	int accum = std::accumulate(logs.begin(), logs.end(), 0, [&](auto& acc, const auto& it) {
		if (it.level == Level::Error && it != it_prev) {
			acc += (it.time.get_int() - it_prev.time.get_int());
			it_prev = it;
			return acc;
		}
		return acc;
	});
	
	std::cout << accum/(levels[Level::Error] - 1) << '\n';


	std::cout << "\n=========THE MOST SEND MESSAGE========\n";
	auto it_max = std::max_element(messages.begin(), messages.end(), [](const auto& a, const auto& b) { return a.second < b.second; });

	std::cout << it_max->first << ": " << it_max->second << '\n';	

	
	return 0;
}