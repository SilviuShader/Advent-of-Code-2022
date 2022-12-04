#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum game_move
{
	rock,
	paper,
	scissors
};

game_move g_win_moves[] = {paper, scissors, rock};
game_move g_lose_moves[] = {scissors, rock, paper};

int match_outcome(const game_move opponent, const game_move player)
{
	if (opponent == player)
		return 3;

	return (player == g_win_moves[opponent]) * 6;
}

int total_score(const vector<pair<game_move, game_move>>& game_moves)
{
	auto total_score = 0;
	constexpr int object_scores[] = {1, 2, 3};
	for (auto& move : game_moves)
	{
		const auto object_score = object_scores[move.second];
		total_score += object_score;
		total_score += match_outcome(move.first, move.second);
	}
	return total_score;
}

int main()
{
	vector<pair<game_move, game_move>> game_moves1;
	vector<pair<game_move, game_move>> game_moves2;

	ifstream fin("input.txt");

	char opponent, player;
	while (fin >> opponent >> player)
	{
		auto opponent_move = static_cast<game_move>(opponent - 'A');
		game_moves1.emplace_back(opponent_move, static_cast<game_move>(player - 'X'));

		game_move player_move = opponent_move;
		switch (player)
		{
		case 'X':
			player_move = g_lose_moves[opponent_move];
			break;
		case 'Y':
			player_move = opponent_move;
			break;
		case 'Z':
			player_move = g_win_moves[opponent_move];
			break;
		default: ;
		}
		game_moves2.emplace_back(opponent_move, player_move);
	}

	fin.close();

	cout << total_score(game_moves1) << endl;
	cout << total_score(game_moves2) << endl;

	return 0;
}
