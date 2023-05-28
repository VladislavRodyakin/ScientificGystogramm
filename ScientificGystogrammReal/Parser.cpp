#include "Parser.hpp"
#include <iostream>
#include <ios>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


Parser::Parser(std::istream& _input) :input{ _input } {
}

Parser::~Parser() {
}

std::vector<int> Parser::parse(std::istream& inp) {
	std::vector <int> result;
	int input;
	std::string line;
	while (std::getline(inp, line)) {
		if (line.empty()) continue;
		std::istringstream iss(line);
		while (iss >> input)
			result.push_back(input);
	}
	return result;
}