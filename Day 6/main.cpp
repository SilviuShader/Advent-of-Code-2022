#include <iostream>
#include <fstream>
#include <unordered_set>
#include <queue>

using namespace std;

int Solve(const string& str, int n)
{
	auto size = str.size();
	auto c_str = str.c_str();

	int chr_occurences['z' - 'a' + 1];
	memset(chr_occurences, 0, sizeof(chr_occurences));
	auto distinct_chars = 0;

	queue<int> currently_occupied;

	int result = -1;

	for (auto i = 0; i < size; i++)
	{
		auto chr = c_str[i];
		auto chr_index = chr - 'a';

		currently_occupied.push(chr_index);
		if (currently_occupied.size() > n)
		{
			auto first = currently_occupied.front();
			currently_occupied.pop();

			chr_occurences[first]--;
			if (chr_occurences[first] == 0)
				distinct_chars--;
		}

		chr_occurences[chr_index]++;
		if (chr_occurences[chr_index] == 1)
			distinct_chars++;

		if (distinct_chars == n)
		{
			result = i + 1;
			break;
		}
	}

	return result;
}

int main()
{
	ifstream fin("input.txt");
	string str;
	fin >> str;
	fin.close();

	cout << Solve(str, 4) << " " << Solve(str, 14) << endl;

	return 0;
}