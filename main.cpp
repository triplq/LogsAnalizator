#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <unordered_map>
#include "logentry.h"

int main() {
	std::vector<LogEntry> logs;
	size_t counter = 0;
	std::unordered_map<Level, size_t> levels;
	std::unordered_map<std::string, size_t> subsystems;

	std::string line;

	std::ifstream in;
	in.open("Resources/log.txt");
	if (in.is_open()) {
		while (std::getline(in, line)) {
			try {
				logs.push_back(LogEntry(line));
				levels[logs[logs.size()-1].level]++;

				subsystems[logs[logs.size()-1].subsystem]++;
			} catch (std::invalid_argument) {
				counter++;
			}
		}
	}
	in.close();

	std::vector<std::pair<std::string, size_t>> subsystems_vector {std::make_move_iterator(subsystems.begin()), std::make_move_iterator(subsystems.end())};

	std::sort(subsystems_vector.begin(), subsystems_vector.end(), [] (const auto& a, const auto& b){
																									return a.second > b.second;
	}); 

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
	
	return 0;
}