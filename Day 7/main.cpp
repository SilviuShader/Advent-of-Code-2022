#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

struct folder
{
	vector<pair<int, string>>      files;
	unordered_map<string, folder*> folders;
	folder*                        parent      = nullptr;
	int                            folder_size = 0; 
};

int result1 = 0;
int result2 = -1;

void calculate_size(folder* folder)
{
	folder->folder_size = 0;

	for (const auto& file : folder->files)
		folder->folder_size += file.first;

	for (const auto& sub_folder : folder->folders)
	{
		calculate_size(sub_folder.second);
		folder->folder_size += sub_folder.second->folder_size;
	}
}

void solve1(const folder* folder)
{
	if (folder->folder_size <= 100000)
		result1 += folder->folder_size;

	for (const auto& sub_folder : folder->folders)
		solve1(sub_folder.second);
}

void solve2(folder* root, const folder* folder)
{
	const auto free_space = 70000000 - root->folder_size;
	if (folder->folder_size + free_space >= 30000000)
	{
		if (result2 == -1)
			result2 = folder->folder_size;
		else
			result2 = min(result2, folder->folder_size);
	}

	for (const auto& sub_folder : folder->folders)
		solve2(root, sub_folder.second);
}

void free_memory(folder* folder)
{
	folder->parent = nullptr;

	for (const auto& sub_folder : folder->folders)
	{
		free_memory(sub_folder.second);
		folder->folders[sub_folder.first] = nullptr;
	}

	folder->folders.clear();
	folder->files.clear();
	delete folder;
	folder = nullptr;
}

int main()
{
	auto root = new folder();
	auto current_folder = root;

	root->parent = nullptr;

	ifstream fin("input.txt");

	string current_line;
	bool listing_files = false;

	while (getline(fin, current_line))
	{
		stringstream line_stream;
		line_stream << current_line;

		if (current_line.at(0) == '$')
			listing_files = false;

		if (listing_files)
		{
			if (current_line.at(0) >= '0' && current_line.at(1) <= '9')
			{
				int size;
				string filename;
				line_stream >> size >> filename;
				auto file = make_pair(size, filename);
				current_folder->files.push_back(file);
			}
			else
			{
				string dir, dir_name;
				line_stream >> dir >> dir_name;

				if (current_folder->folders.find(dir_name) == current_folder->folders.end())
				{
					auto new_folder = new folder();
					new_folder->parent = current_folder;
					current_folder->folders[dir_name] = new_folder;
				}
			}
		}

		if (!listing_files)
		{
			char dollar_sign;
			string instruction;
			line_stream >> dollar_sign >> instruction;
			if (instruction == "cd")
			{
				string path;
				line_stream >> path;
				if (path == "..")
					current_folder = current_folder->parent;
				else if (path == "/")
					current_folder = root;
				else
				{
					if (current_folder->folders.find(path) == current_folder->folders.end())
					{
						auto new_folder = new folder();
						new_folder->parent = current_folder;
						current_folder->folders[path] = new_folder;
					}

					current_folder = current_folder->folders[path];
				}
			}
			else if (instruction == "ls")
				listing_files = true;
			
		}
	}

	fin.close();

	calculate_size(root);
	solve1(root);
	solve2(root, root);

	cout << result1 << " " << result2 << endl;

	free_memory(root);
	root = nullptr;

	return 0;
}