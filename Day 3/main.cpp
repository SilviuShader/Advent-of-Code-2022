#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int object_priority(const char object)
{
	if (object >= 'a' && object <= 'z')
		return object - 'a' + 1;

	if (object >= 'A' && object <= 'Z')
		return object - 'A' + 27;

	return -1;
}

int rucksack_priority(vector<int>& rucksack)
{
	const auto half = static_cast<int>(rucksack.size()) >> 1;
	sort(rucksack.begin(), rucksack.begin() + half);
	sort(rucksack.begin() + half, rucksack.end());
	auto i0 = 0;
	auto i1 = half;

	while (i0 < half && i1 < static_cast<int>(rucksack.size()))
	{
		const auto left = rucksack[i0];
		const auto right = rucksack[i1];
		if (left == right)
			return left;
		if (left < right)
			i0++;
		else
			i1++;
	}

	cout << "Common item was not found." << endl;

	return -1;
}

int common_item(const vector<vector<int>>::iterator& begin, const vector<vector<int>>::iterator& end)
{
	vector<int> indices;

	for (auto rucksack = begin; rucksack != end; ++rucksack)
		indices.push_back(0);

	auto found = false;
	while (!found)
	{
		auto index = 0;
		auto previous_value = -1;

		found = true;

		for (auto rucksack = begin; rucksack != end; ++rucksack)
		{
			auto& rucksack_object = *rucksack;
			const auto value = rucksack_object[indices[index]];

			if (index == 0)
				previous_value = value;
			else if (previous_value != value)
				found = false;

			index++;
		}

		if (found)
			return previous_value;

		auto min_value = 100;
		index = 0;
		auto min_index = 0;
		for (auto rucksack = begin; rucksack != end; ++rucksack)
		{
			auto& rucksack_object = *rucksack;
			const auto value = rucksack_object[indices[index]];

			if (value < min_value)
			{
				min_value = value;
				min_index = index;
			}

			index++;
		}
		indices[min_index]++;
	}

	return 0;
}

int main()
{
	ifstream fin("input.txt");
	string line;
	vector<vector<int>> rucksacks;

	while (fin >> line)
	{
		vector<int> rucksack;
		for (const auto object : line)
		{
			auto priority = object_priority(object);
			if (priority == -1)
				continue;
			rucksack.push_back(priority);
		}
		rucksacks.push_back(rucksack);
	}

	fin.close();

	auto result1 = 0;
	for (auto& rucksack : rucksacks)
		result1 += rucksack_priority(rucksack);

	cout << result1 << endl;

	for (auto& rucksack : rucksacks)
		sort(rucksack.begin(), rucksack.end());

	auto result2 = 0;
	for (auto i = 0; i < static_cast<int>(rucksacks.size()); i += 3)
		result2 += common_item(rucksacks.begin() + i, rucksacks.begin() + i + 3);

	cout << result2 << endl;

	return 0;
}
