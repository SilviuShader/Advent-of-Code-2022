#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct stack_instruction
{
	int quantity;
	int from;
	int to;
};

void execute_stack_instruction_v1(vector<vector<char>>& stacks, const stack_instruction& instruction)
{
	for (auto i = 0; i < instruction.quantity; i++)
	{
		auto value = stacks[instruction.from].back();
		stacks[instruction.from].pop_back();
		stacks[instruction.to].push_back(value);
	}
}

void execute_stack_instruction_v2(vector<vector<char>>& stacks, const stack_instruction& instruction)
{
	for (auto i = stacks[instruction.from].size() - instruction.quantity; i < stacks[instruction.from].size(); i++)
	{
		auto value = stacks[instruction.from][i];
		stacks[instruction.to].push_back(value);
	}

	for (auto i = 0; i < instruction.quantity; i++)
		stacks[instruction.from].pop_back();
}

int main()
{
	ifstream fin("input.txt");
	string line_string;

	vector<string> raw_config_strings;

	int stacks_count = 0;

	while (getline(fin, line_string))
	{
		stringstream line_stream;

		line_stream << line_string;

		int tmp;
		if (line_stream >> tmp)
		{
			stacks_count = 1;
			while (line_stream >> tmp)
				stacks_count++;
			break;
		}
		raw_config_strings.push_back(line_string);
	}
	getline(fin, line_string);

	vector<vector<char>> stacks(stacks_count);

	for (auto i = static_cast<int>(raw_config_strings.size()) - 1; i >= 0; i--)
	{
		const auto& line = raw_config_strings[i];
		for (auto j = 1, stack_index = 0; j < static_cast<int>(line.size()); j += 4, stack_index++)
			if (line[j] != ' ')
				stacks[stack_index].push_back(line[j]);
	}

	vector<vector<char>> stacks_v1(stacks);
	vector<vector<char>> stacks_v2(stacks);

	vector<stack_instruction> instructions;

	string tmp_word;
	stack_instruction crt_instruction{};
	while (fin >> tmp_word >> crt_instruction.quantity >> tmp_word >> crt_instruction.from >> tmp_word >> crt_instruction.to)
	{
		crt_instruction.from--;
		crt_instruction.to--;
		instructions.push_back(crt_instruction);
	}
	fin.close();

	for (const auto& instruction : instructions)
		execute_stack_instruction_v1(stacks_v1, instruction);

	for (const auto& instruction : instructions)
		execute_stack_instruction_v2(stacks_v2, instruction);

	for (auto& current_stack : stacks_v1)
		cout << current_stack.back();
	cout << endl;

	for (auto& current_stack : stacks_v2)
		cout << current_stack.back();
	
	return 0;
}