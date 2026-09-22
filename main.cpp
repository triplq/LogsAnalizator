#include <fstream>
#include <iostream>
#include <stdexcept>
#include "logentry.h"

int main() {
	std::vector<LogEntry> logs;
	size_t counter = 0;

	std::string line;

	std::ifstream in;
	in.open("Resources/log.txt");
	if (in.is_open()) {
		while (std::getline(in, line)) {
			try {
				logs.push_back(LogEntry(line));
			} catch (std::invalid_argument) {
				counter++;
			}
		}
	}
	in.close();

	std::cout << counter << '\n';
	
	return 0;
}