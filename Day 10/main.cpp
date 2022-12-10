#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct screen_instruction
{
	string op;
	int    value = 0;
	int    cycles;
};

int main()
{
	vector<screen_instruction> instructions;

	ifstream fin("input.txt");

	string op;
	while (fin >> op)
	{
		int value = 0;
		int cycles = 1;
		if (op == "addx")
		{
			fin >> value;
			cycles = 2;
		}
		instructions.push_back(screen_instruction{ op, value, cycles });
	}

	fin.close();
	
	auto instruction_index = 0;
	auto current_instruction_cycle = 0;
	auto x = 1;

	auto result1 = 0;

	char screen[8][40] = {};

	for (auto cycle = 1; true; cycle++)
	{
		if (instruction_index >= instructions.size())
			break;

		const auto& instr = instructions[instruction_index];

		current_instruction_cycle++;

		if (cycle >= 20)
			if ((cycle - 20) % 40 == 0)
				result1 += cycle * x;

		const auto column = (cycle - 1) % 40;
		const auto row = (cycle - 1) / 40;

		if (column == x - 1 || column == x || column == x + 1)
			screen[row][column] = '#';
		else
			screen[row][column] = '.';

		if (current_instruction_cycle >= instr.cycles)
		{
			if (instr.op == "addx")
				x += instr.value;

			instruction_index++;
			current_instruction_cycle = 0;
		}
	}

	cout << result1 << endl;

	for (const auto& row : screen)
	{
		for (char cell : row)
			cout << cell;
		cout << endl;
	}

	return 0;
}