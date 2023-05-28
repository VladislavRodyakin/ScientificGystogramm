#include "Gyst.hpp"
#include <vector>
#include <map>

Gyst::Gyst(int _min, int _max, int _count): min{ _min }, max{ _max }, count{ _count } {
	window = (max - min)/count;
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
			continue;
		}
	}
}

Gyst::Gyst(int _min, int _max, int _count, std::vector<int> _data): min { _min }, max{ _max }, count{ _count } {
	window = (max - min) / count;
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

Gyst Gyst::operator+(const Gyst& another_hist) const {
	if (!prop_validate(*this, another_hist)) {
		throw std::invalid_argument("invalid operation '+' ");
	}
	Gyst result{ *this };
	for (const auto node : another_hist.data) {
		result.data[node.first] += node.second;
	}
	return result;
}

Gyst Gyst::operator-(const Gyst& another_hist) const
{
	if (!prop_validate(*this, another_hist)) {
		throw std::invalid_argument("invalid operation '-' ");
	}
	Gyst result(*this);
	for (auto const map_node : another_hist.data) {
		int difference = result.data.at(map_node.first) - another_hist.data.at(map_node.first);
		if (difference < 0) {
			result.data.at(map_node.first) = 0;
		}
		else {
			result.data.at(map_node.first) = difference;
		}
	}
	return result;
}

bool Gyst::operator==(const Gyst& another_hist) const {
	if (!prop_validate(*this, another_hist)) {
		throw std::invalid_argument("invalid operation '==' ");
	}
	return data == another_hist.data;
}

bool Gyst::operator!=(const Gyst& another_hist) const {
	if (!prop_validate(*this, another_hist)) {
		throw std::invalid_argument("invalid operation '==' ");
	}
	return data != another_hist.data;
}

auto Gyst::begin() const {
	return data.begin();
}

auto Gyst::end() const {
	return data.end();
}

const int& Gyst::at(int key_for_bin) const {
	return data.at(key_for_bin);
}

std::string Gyst::Show_Gyst() const {
	std::string output;
	for (auto& map_node : data)
	{
		output += map_node.first + " " + map_node.second + '\n';
	}
	return output;
}