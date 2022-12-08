#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	ifstream fin("input.txt");

	bool first_line = true;
	string line;
	int line_length = 0;

	vector<vector<int>> trees;

	while (fin >> line)
	{
		if (first_line)
		{
			line_length = line.size();
			first_line = false;
			vector<int> tmp_line(line_length + 2, -1);
			trees.push_back(tmp_line);
		}

		const auto c_str = line.c_str();

		vector<int> numbers_line(line_length + 2, -1);
		for (auto i = 1; i <= line_length; i++)
			numbers_line[i] = c_str[i - 1] - '0';
		trees.push_back(numbers_line);
	}

	trees.push_back(trees[0]);

	fin.close();

	vector<vector<int>> left_max(trees.size(), vector<int>(line_length + 2, -1));
	vector<vector<int>> top_max(trees.size(), vector<int>(line_length + 2, -1));
	vector<vector<int>> right_max(trees.size(), vector<int>(line_length + 2, -1));
	vector<vector<int>> bottom_max(trees.size(), vector<int>(line_length + 2, -1));

	for (auto i = 1; i < trees.size() - 1; i++)
	{
		for (auto j = 1; j < trees[i].size() - 1; j++)
		{
			left_max[i][j] = max(left_max[i][j - 1], trees[i][j - 1]);
			top_max[i][j] = max(top_max[i - 1][j], trees[i - 1][j]);
		}
	}

	for (auto i = trees.size() - 2; i >= 1; i--)
	{
		for (auto j = trees[i].size() - 2; j >= 1; j--)
		{
			right_max[i][j] = max(right_max[i][j + 1], trees[i][j + 1]);
			bottom_max[i][j] = max(bottom_max[i + 1][j], trees[i + 1][j]);
		}
	}

	auto result1 = 0;
	auto result2 = 0;

	int dir_i[] = { 0, -1, 0, 1 };
	int dir_j[] = { -1, 0, 1, 0 };

	for (auto i = 1; i < trees.size() - 1; i++)
	{
		for (auto j = 1; j < trees[i].size() - 1; j++)
		{
			if (trees[i][j] > left_max[i][j] ||
				trees[i][j] > top_max[i][j] ||
				trees[i][j] > right_max[i][j] ||
				trees[i][j] > bottom_max[i][j])
			{
				result1++;

				int product = 1;

				for (auto dir = 0; dir < 4; dir++)
				{
					auto d_i = dir_i[dir];
					auto d_j = dir_j[dir];

					auto p_i = i + d_i;
					auto p_j = j + d_j;

					int current_value = -1;

					int number = 0;

					while (true)
					{
						current_value = trees[p_i][p_j];

						if (current_value != -1)
							number++;

						if (current_value == -1 || current_value >= trees[i][j])
							break;

						p_i += d_i;
						p_j += d_j;
					}

					product *= number;
				}

				result2 = max(result2, product);
			}
		}
	}

	cout << result1 << " " << result2 << endl;

	return 0;
}