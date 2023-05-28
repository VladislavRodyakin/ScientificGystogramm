#include "Gyst.hpp"
#include <vector>
#include <map>

Gyst::Gyst(int _min, int _max, int _count): min{ _min }, max{ _max }, count{ _count } {
	if (max - min < count-1)
		throw std::invalid_argument("Number of bins must be equal or less than difference between max and min.");
	window = (max - min)/(count-1);
	for (int i = 0; i < count; i++)
		data[i] = 0;
}

void Gyst::add_elem(int elem){
	if (elem < min)
		data[0]++;
	if (elem > max)
		data[count - 1]++;
	for (int i = 0; i < count; i++) {
		if (min + (i * window) < elem && elem < min + ((i + 1) * window)) {
			data[i]++;
			break;
		}
	}
}

Gyst::Gyst(int _min, int _max, int _count, std::vector<int> _data): min { _min }, max{ _max }, count{ _count } {
	if (max - min < count - 1)
		throw std::invalid_argument("Number of bins must be equal or less than difference between max and min.");
	window = (max - min) / (count - 1);
	for (int i = 0; i < count; i++)
		data[i] = 0;
	for (int& i : _data) {
		if (i < min)
			data[0]++;
		else if (i > max)
			data[count - 1]++;
		else
			add_elem(i);
	}
}

//Gyst::Gyst(const Gyst& other) : min{ other.min }, max{ other.max }, count{ other.count }, window{ other.window } {
//	data = other.data;
//}
//
//Gyst& Gyst::operator=(const Gyst& other) {
//	if (this == &from)
//		return *this;
//	this->min = other.min;
//	this->max = other.max;
//	this->count = other.count;
//	this->window = other.window;
//	this->data = other.data;
//	return *this;
//}

void Gyst::add_data(std::vector<int> _data) {
	for (int& i : _data) {
		if (i < min)
			data[0]++;
		else if (i > max)
			data[count - 1]++;
		else
			add_elem(i);
	}
}

void Gyst::add_data(int _data) {
	add_elem(_data);
}

int Gyst::prop_validate(const Gyst& first_hist, const Gyst& second_hist) {
	if (first_hist.min == second_hist.min && first_hist.max == second_hist.max && first_hist.count == second_hist.count) {
		return 1;
	}
	return 0;
}

Gyst Gyst::operator+(const Gyst& other) const {
	if (!(this->min == other.min && this->max == other.max && this->count == other.count))
		throw std::invalid_argument("'+' operation could only be conducted on gystogramms with equal min, max and bin count");
	Gyst result(*this);
	for (auto& node_data: other.data)
		result.data[node_data.first] += node_data.second;
	return result;
}

Gyst Gyst::operator-(const Gyst& other) const {
	if (!(this->min == other.min && this->max == other.max && this->count == other.count))
		throw std::invalid_argument("'-' operation could only be conducted on gystogramms with equal min, max and bin count");
	Gyst result(*this);
	for (auto& node_data: other.data) {
		int difference = result.data.at(node_data.first) - other.data.at(node_data.first);
		if (difference < 0)
			result.data.at(node_data.first) = 0;
		else
			result.data.at(node_data.first) = difference;
	}
	return result;
}

bool Gyst::operator==(const Gyst& other) const {
	if (!(this->min == other.min && this->max == other.max && this->count == other.count))
		throw std::invalid_argument("'==' operation could only be conducted on gystogramms with equal min, max and bin count");
	return this->data == other.data;
}

bool Gyst::operator!=(const Gyst& other) const {
	if (!(this->min == other.min && this->max == other.max && this->count == other.count))
		throw std::invalid_argument("'!=' operation could only be conducted on gystogramms with equal min, max and bin count");
	return data != other.data;
}

const int& Gyst::at(int bin_num) const {
	return data.at(bin_num);
}

std::string Gyst::string_format() const {
	std::string output;
	for (auto& node_data: data)
		output += node_data.first + " " + node_data.second + '\n';
	return output;
}