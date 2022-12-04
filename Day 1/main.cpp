#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	string str;
	vector<int> sums;
	sums.push_back(0);
	
	ifstream fin("input.txt");

	while (getline(fin, str))
	{
		if (str.size() > 1)
			sums[sums.size() - 1] += stoi(str);
		else
			sums.push_back(0);
	}

	fin.close();

	auto max1 = 0;
	auto max2 = 0;
	auto max3 = 0;

	for (auto sum : sums)
	{
		if (sum > max1)
		{
			max3 = max2;
			max2 = max1;
			max1 = sum;
		}
		else
		{
			if (sum > max2)
			{
				max3 = max2;
				max2 = sum;
			}
			else
			{
				max3 = max(max3, sum);
			}
		}
	}

	cout << max1 << " " << max1 + max2 + max3 << endl;

	return 0;
}