#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct elves_pair
{
	pair<int, int> interval1;
	pair<int, int> interval2;
};

bool fully_overlap(const elves_pair& current_pair)
{
	const auto& interval1 = current_pair.interval1;
	const auto& interval2 = current_pair.interval2;
	
	if (interval1.first >= interval2.first && interval1.second <= interval2.second)
		return true;
	else if (interval2.first >= interval1.first && interval2.second <= interval1.second)
		return true;

	return false;
}

bool partial_overlap(const elves_pair& current_pair)
{
	const auto& interval1 = current_pair.interval1;
	const auto& interval2 = current_pair.interval2;

	pair<int, int> intersection = make_pair(max(interval1.first, interval2.first), 
		min(interval1.second, interval2.second));

	return intersection.first <= intersection.second;
}

int main()
{
	ifstream fin("input.txt");

	int b1, e1, b2, e2;
	char tmp;

	vector<elves_pair> elves;

	while (fin >> b1 >> tmp >> e1 >> tmp >> b2 >> tmp >> e2)
	{
		elves_pair current_pair;
		current_pair.interval1 = make_pair(b1, e1);
		current_pair.interval2 = make_pair(b2, e2);
		elves.push_back(current_pair);
	}

	fin.close();

	auto result1 = 0;
	auto result2 = 0;

	for (const auto& current_pair : elves)
	{
		if (fully_overlap(current_pair))
			result1++;

		if (partial_overlap(current_pair))
			result2++;
	}

	cout << result1 << " " << result2 << endl;

	return 0;
}