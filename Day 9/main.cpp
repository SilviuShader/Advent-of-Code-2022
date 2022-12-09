#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

constexpr auto dirs_count = 9;
int dir_x[] = { 0, 0, -1, 0, 1, -1, -1, 1, 1 };
int dir_y[] = { 0, -1, 0, 1, 0, -1, 1, -1, 1 };

bool is_near_head(const pair<int, int>& tail, const pair<int, int>& head)
{
	for (auto i = 0; i < dirs_count; i++)
	{
		auto head_neighbor = make_pair(head.first + dir_x[i], head.second + dir_y[i]);
		if (head_neighbor == tail)
			return true;
	}

	return false;
}

int manhattan_distance(const pair<int, int>& a, const pair<int, int>& b)
{
	return abs(a.first - b.first) + abs(a.second - b.second);
}

void process_single_step(const char step, pair<int, int>& tail, pair<int, int>& head)
{
	switch (step)
	{
	case 'L':
		head.first--;
		break;
	case 'R':
		head.first++;
		break;
	case 'U':
		head.second++;
		break;
	case 'D':
		head.second--;
		break;
	}

	int distances[dirs_count];
	for (int& distance : distances)
		distance = 10;

	const int dist_head_tail = manhattan_distance(head, tail);

	for (auto i = 0; i < dirs_count; i++)
	{
		auto new_tail_pos = make_pair(tail.first + dir_x[i], tail.second + dir_y[i]);
		if (!is_near_head(new_tail_pos, head))
			continue;

		if (dist_head_tail >= 3)
			distances[i] = manhattan_distance(new_tail_pos, head);
		else
			distances[i] = manhattan_distance(new_tail_pos, tail);
	}

	auto chosen_dir = 0;

	for (auto i = 0; i < dirs_count; i++)
		if (distances[chosen_dir] > distances[i])
			chosen_dir = i;
	
	tail = make_pair(tail.first + dir_x[chosen_dir], tail.second + dir_y[chosen_dir]);


}

int solve(const vector<pair<char, int>>& steps, vector<pair<int, int>>& knots)
{
	set<pair<int, int>> tail_positions;
	tail_positions.insert(knots[knots.size() - 1]);

	for (const auto& current_step : steps)
	{
		for (auto i = 0; i < current_step.second; i++)
		{
			for (auto j = 0; j < knots.size() - 1; j++)
			{
				auto& head = knots[j];
				auto& tail = knots[j + 1];

				process_single_step((j == 0) * current_step.first, tail, head);

				if (j == knots.size() - 2)
					if (tail_positions.find(tail) == tail_positions.end())
						tail_positions.insert(tail);
			}
		}
	}

	return tail_positions.size();
}

int main()
{
	ifstream fin("input.txt");
	vector<pair<char, int>> steps;
	vector<pair<int, int>> knots1(2, make_pair(0, 0));
	vector<pair<int, int>> knots2(10, make_pair(0, 0));

	pair<char, int> step;
	while (fin >> step.first >> step.second)
		steps.push_back(step);

	fin.close();

	cout << solve(steps, knots1) << endl;
	cout << solve(steps, knots2) << endl;

	return 0;
}