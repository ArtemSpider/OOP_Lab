#pragma once

#include <string>
#include <fstream>

#include "Board.h"
#include "Boards.h"


class GameIO
{
	static string GridToString(ChessBoard* board)
	{
		string grid;
		for (int i = 0; i < board->SIZE.y; i++)
		{
			for (int j = 0; j < board->SIZE.x; j++)
			{
				const Piece* p = board->GetPieceAt({ j, i });

				char c = ' ';
				if (p != nullptr)
				{
					switch (p->GetType())
					{
					case PieceType::Pawn: c = 'p'; break;
					case PieceType::Knight: c = 'n'; break;
					case PieceType::Bishop: c = 'b'; break;
					case PieceType::Rook: c = 'r'; break;
					case PieceType::Queen: c = 'q'; break;
					case PieceType::King: c = 'k'; break;
					}

					if (p->GetTeam() == PlayerTeam::White)
						c = toupper(c);
				}

				grid += c;
			}
			grid += '\n';
		}
		return grid;
	}

	static string ToChessNotation(Position pos)
	{
		return string(1, 'a' + pos.x) + string(1, '1' + pos.y);
	}
	static Position FromChessNotation(string pos)
	{
		return Position(pos[0] - 'a', pos[1] - '1');
	}

	static string MovesToString(const vector<PieceMove>& moves)
	{
		string res;
		for (const auto& m : moves)
			res += ToChessNotation(m.from) + ToChessNotation(m.to) + '\n';
		return res;
	}
public:
	static void Save(ChessBoard* board, string pathToFile)
	{
		ofstream file;
		file.open(pathToFile);
		file << MovesToString(board->GetMovesRecord());
	}

	static ChessBoard* Load(string pathToFile)
	{
		ChessBoard* board = CreateBoard();

		ifstream file;
		file.open(pathToFile);

		string s;
		while (file >> s)
		{
			Position from = FromChessNotation(s.substr(0, 2));
			Position to = FromChessNotation(s.substr(2, 2));

			board->MovePiece(from, to);
		}

		return board;
	}
};