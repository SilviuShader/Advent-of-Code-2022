#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum Move
{
	Rock,
	Paper,
	Scissors
};

Move g_winMoves[]  = { Move::Paper,    Move::Scissors, Move::Rock };
Move g_loseMoves[] = { Move::Scissors, Move::Rock,     Move::Paper };

int MatchOutcome(Move opponent, Move player)
{
	if (opponent == player)
		return 3;

	return (player == g_winMoves[opponent]) * 6;
}

int TotalScore(const vector<pair<Move, Move>>& gameMoves)
{
	auto totalScore = 0;
	int objectScores[] = { 1, 2, 3 };
	for (auto& move : gameMoves)
	{
		auto objectScore = objectScores[move.second];
		totalScore += objectScore;
		totalScore += MatchOutcome(move.first, move.second);
	}
	return totalScore;
}

int main()
{
	vector<pair<Move, Move>> gameMoves1;
	vector<pair<Move, Move>> gameMoves2;

	ifstream fin("input.txt");

	char opponent, player;
	while (fin >> opponent >> player)
	{
		Move opponentMove = Move(opponent - 'A');
		gameMoves1.push_back(make_pair(opponentMove, Move(player - 'X')));
		
		Move playerMove = opponentMove;
		switch (player)
		{
		case 'X':
			playerMove = g_loseMoves[opponentMove];
			break;
		case 'Y':
			playerMove = opponentMove;
			break;
		case 'Z':
			playerMove = g_winMoves[opponentMove];
			break;
		}
		gameMoves2.push_back(make_pair(opponentMove, playerMove));
	}

	fin.close();

	cout << TotalScore(gameMoves1) << endl;
	cout << TotalScore(gameMoves2) << endl;

	return 0;
}