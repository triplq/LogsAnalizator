#include "stats.h"
#include <iostream>
#include <numeric>

void all_logs_at_hour(const std::vector<LogEntry> &logs) {
	std::cout << "\n=========ALL LOGS AT X HOUR========\n";
	int hour;
	std::cout << "ENTER AN HOUR: ";
	std::cin >> hour;

	auto it_hour = logs.begin();
	while ((it_hour = std::find_if(it_hour, logs.end(), [&](const auto& a){ return a.time.get_hours() == hour; })) != logs.end()) {
		std::cout << *it_hour << '\n';
		it_hour++;
	}
}

void oldest_line(const std::vector<LogEntry> &logs) {
	std::cout << "\n=========THE OLDEST LINE========\n";
	auto it_old = std::max_element(logs.begin(), logs.end(), [](const auto& a, const auto& b){ return a.time > b.time && a.date >= b.date; });
	std::cout << *it_old << '\n';
}

void newest_line(const std::vector<LogEntry> &logs) {
	std::cout << "\n=========THE NEWEST LINE========\n";
	auto it_new = std::max_element(logs.begin(), logs.end(), [](const auto& a, const auto& b){ return a.time < b.time && a.date <= b.date; });
	std::cout << *it_new << '\n';
}

void interval_between_errors(const std::vector<LogEntry> &logs, std::unordered_map<Level, size_t>& levels) {
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
}

void most_send_message(std::unordered_map<std::string, size_t>& messages) {
	std::cout << "\n=========THE MOST SEND MESSAGE========\n";
	auto it_max = std::max_element(messages.begin(), messages.end(), [](const auto& a, const auto& b) { return a.second < b.second; });

	std::cout << it_max->first << ": " << it_max->second << "\n\n";	
}