#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int ObjectPriority(char object)
{
	if (object >= 'a' && object <= 'z')
		return object - 'a' + 1;

	if (object >= 'A' && object <= 'Z')
		return object - 'A' + 27;

	return -1;
}

int RucksackPriority(vector<int>& rucksack)
{
	auto half = rucksack.size() >> 1;
	sort(rucksack.begin(), rucksack.begin() + half);
	sort(rucksack.begin() + half, rucksack.end());
	auto i0 = 0;
	auto i1 = half;

	while (i0 < half && i1 < rucksack.size())
	{
		auto left = rucksack[i0];
		auto right = rucksack[i1];
		if (left == right)
			return left;
		else if (left < right)
			i0++;
		else
			i1++;
	}

	cout << "Common item was not found." << endl;

	return -1;
}

int CommonItem(vector<vector<int>>::iterator begin, vector<vector<int>>::iterator end)
{
	vector<int> indices;

	for (auto rucksack = begin; rucksack != end; rucksack++)
		indices.push_back(0);

	auto found = false;
	while (!found)
	{
		auto index = 0;
		auto previousValue = -1;

		found = true;

		for (auto rucksack = begin; rucksack != end; rucksack++)
		{
			auto& rucksackObject = *rucksack;
			auto value = rucksackObject[indices[index]];
			
			if (index == 0)
				previousValue = value;
			else if (previousValue != value)
				found = false;

			index++;
		}

		if (found)
			return previousValue;

		auto minValue = 100;
		index = 0;
		auto minIndex = 0;
		for (auto rucksack = begin; rucksack != end; rucksack++)
		{
			auto& rucksackObject = *rucksack;
			auto value = rucksackObject[indices[index]];

			if (value < minValue)
			{
				minValue = value;
				minIndex = index;
			}

			index++;
		}
		indices[minIndex]++;
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
		for (auto object : line)
		{
			auto priority = ObjectPriority(object);
			if (priority == -1)
				continue;
			rucksack.push_back(priority);
		}
		rucksacks.push_back(rucksack);
	}

	fin.close();

	auto result1 = 0;
	for (auto& rucksack : rucksacks)
		result1 += RucksackPriority(rucksack);

	cout << result1 << endl;

	for (auto& rucksack : rucksacks)
		sort(rucksack.begin(), rucksack.end());

	auto result2 = 0;
	for (auto i = 0; i < rucksacks.size(); i+=3)
		result2 += CommonItem(rucksacks.begin() + i, rucksacks.begin() + i + 3);

	cout << result2 << endl;

	return 0;
}