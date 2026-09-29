#include "stats.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>

void all_logs_at_hour(const std::vector<LogEntry> &logs) {
	std::cout << "\n=========ALL LOGS AT X HOUR========\n";
	unsigned int hour;
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
	auto it_old = std::max_element(logs.begin(), logs.end(), [](const auto& a, const auto& b){ return a.date > b.date || (a.date == b.date && a.time > b.time); });
	std::cout << *it_old << '\n';
}

void newest_line(const std::vector<LogEntry> &logs) {
	std::cout << "\n=========THE NEWEST LINE========\n";
	auto it_new = std::max_element(logs.begin(), logs.end(), [](const auto& a, const auto& b){ return a.date < b.date || (a.date == b.date && a.time < b.time); });
	std::cout << *it_new << '\n';
}

void interval_between_errors(const std::vector<LogEntry> &logs) {
	std::cout << "\n=========AVERAGE INTERVAL BETWEEN ERRORS========\n";

	std::vector<int> errors_time;
	for (size_t i = 0; i < logs.size(); i++) {
		if (logs[i].level == Level::Error)
			errors_time.push_back(logs[i].get_int());
	}
	
	std::vector<int> errors_difference;
	std::adjacent_difference(errors_time.begin(), errors_time.end(), std::back_inserter(errors_difference));

	int accum = std::accumulate(errors_difference.begin() + 1, errors_difference.end(), 0, [](auto& acc, const auto& it){ return acc + it; });
	std::cout << accum / errors_difference.size() << '\n';
}

void most_send_message(std::unordered_map<std::string, size_t>& messages) {
	std::cout << "\n=========THE MOST SEND MESSAGE========\n";
	auto it_max = std::max_element(messages.begin(), messages.end(), [](const auto& a, const auto& b) { return a.second < b.second; });

	std::cout << it_max->first << ": " << it_max->second << "\n\n";	
}