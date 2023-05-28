#pragma once
#include <map>
#include <string>
#include <vector>
#include <stdexcept>
//parser->vector <int>
//gyst(int min, int max, int count, vector<int> data);
class Gyst{
public:
	Gyst(int _min, int _max, int _count);
	Gyst(int _min, int _max, int _count, std::vector<int> _data);
	Gyst(const Gyst& other) = default;
	Gyst& operator=(const Gyst& other) = default;

	auto begin() const { return data.begin(); };
	auto end() const { return data.end(); };
	
	Gyst operator+(const Gyst& other) const;
	Gyst operator-(const Gyst& other) const;
	bool operator==(const Gyst& other) const { return data == other.data; };
	bool operator!=(const Gyst& other) const { return data != other.data; };

	void add_data(std::vector<int> _data);
	void add_data(int _data);

	const int& at(int bin_num) const;
	std::string GetResult();

private:
	int min, max, count;
	float window;
	std::map<int, int> data;
	void add_elem(int elem);
	int prop_validate(const Gyst& first_hist, const Gyst& second_hist);
};