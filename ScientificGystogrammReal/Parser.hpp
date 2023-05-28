#pragma once
#include <iostream>
#include <vector>

class Parser {
public:
	Parser(std::istream& input);
	~Parser();
	static std::vector<int> parse(std::istream& inp);
private:
	std::istream& input;
};