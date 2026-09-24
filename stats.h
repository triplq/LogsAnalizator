#pragma once

#include <unordered_map>
#include <vector>
#include "logentry.h"
#include "level.h"

void all_logs_at_hour (const std::vector<LogEntry>&);

void oldest_line (const std::vector<LogEntry>&);
void newest_line (const std::vector<LogEntry>&);

void interval_between_errors (const std::vector<LogEntry>&, std::unordered_map<Level, size_t>&);

void most_send_message (std::unordered_map<std::string, size_t>&);