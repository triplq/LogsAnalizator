#pragma once

#include <iterator>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>
#include "logentry.h"
#include "level.h"

void all_logs_at_hour (const std::vector<LogEntry>&);

void oldest_line (const std::vector<LogEntry>&);
void newest_line (const std::vector<LogEntry>&);

void interval_between_errors (const std::vector<LogEntry>&, std::unordered_map<Level, size_t>&);

void most_send_message (std::unordered_map<std::string, size_t>&);

template <typename KeyExtractor>
auto top_n (const std::vector<LogEntry>& logs, KeyExtractor key, size_t n) {
	if (n < logs.size()) {
		throw std::invalid_argument("Small n");
	}

	using Key = decltype(key(std::declval<LogEntry>()));
	std::unordered_map<Key, size_t> answer;
	for (size_t i = 0; i < logs.size(); i++) {
		answer[key(logs[i])]++;
	}
	std::vector<std::pair<Key, size_t>> answer_vector{answer.begin(), answer.end()};
	std::partial_sort(answer_vector.begin(), answer_vector.begin() + n, answer_vector.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
	answer_vector.resize(n);

	return answer_vector;
};