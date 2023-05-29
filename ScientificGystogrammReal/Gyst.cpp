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
	if (elem <= min) {
		data[0]++;
		return;
	}
	if (elem > max) {
		data[count - 1]++;
		return;
	}
	for (int i = 0; i < count; i++) {
		if (min + (i * window) < elem && elem <= min + ((i + 1) * window)) {
			data[i]++;
			return;
		}
	}
}

Gyst::Gyst(int _min, int _max, int _count, std::vector<int> _data): min { _min }, max{ _max }, count{ _count } {
	if (max - min < count - 1)
		throw std::invalid_argument("Number of bins must be equal or less than difference between max and min.");
	window = (max - min) / (count - 1);
	for (int i = 0; i < count; i++)
		data[i] = 0;
	for (int i : _data) {
		if (i < min)
			data[0]++;
		else if (i > max)
			data[count - 1]++;
		else
			add_elem(i);
	}
}

void Gyst::add_data(std::vector<int> _data) {
	for (int i : _data)
			add_elem(i);
}

void Gyst::add_data(int _data) {
	add_elem(_data);
}

size_t Gyst::begin() const {//this must be a map iterator
	return 0;
}

size_t Gyst::end() const {
	return count - 1;
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

const int& Gyst::at(int it) const {
	return data.at(it);
}

std::string Gyst::string_format() const {
	std::string output;
	for (auto& node_data: data)
		output += std::to_string(node_data.first) + " " + std::to_string(node_data.second) + '\n';
	return output;
}