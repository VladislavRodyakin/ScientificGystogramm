#pragma once
#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include <utility>
//parser->vector <int>
//gyst(int min, int max, int count, vector<int> data);
class Gyst{
public:
	Gyst(int _min, int _max, int _count);
	Gyst(int _min, int _max, int _count, std::vector<int> _data);
	Gyst(const Gyst& other) = default;
	Gyst& operator=(const Gyst& other) = default;

	size_t begin() const;
	size_t end() const;
	/*std::pair<const int, int> begin() const { return data.begin(); };
	std::pair<const int, int> end() const { return data.end(); };*/
	/*result.second = iterstor.first ->
		std::pair<const int, int>*/
	Gyst operator+(const Gyst& other) const;
	Gyst operator-(const Gyst& other) const;
	bool operator==(const Gyst& other) const;
	bool operator!=(const Gyst& other) const;

	void add_data(std::vector<int> _data);
	void add_data(int _data);

	const int& at(int bin_num) const;
	std::string string_format() const;

private:
	int min, max, count;
	float window;
	std::map<int, int> data;
	void add_elem(int elem);
};