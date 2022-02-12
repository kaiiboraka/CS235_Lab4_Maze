//
// Created by Brandon on 2/5/2022.
//

#include "Pathfinder.h"

Pathfinder::Pathfinder()
{

	initialize_random_seed();

	for (int hall = 0; hall < HALL_SIZE; hall++)
	{
		for (int row = 0; row < ROW_SIZE; row++)
		{
			for (int col = 0; col < COL_SIZE; col++)
			{
				maze_grid[col][row][hall] = 1;
				path_grid[col][row][hall] = 1;

			}
		}
	}
}

Pathfinder::~Pathfinder()
{

}

bool Pathfinder::importMaze(string file_name)
{
	cout << "importMaze from " << file_name << endl;

	ifstream checkFile(file_name);
	string lineToCheck;
	int lineCount = 0;
	while (getline(checkFile, lineToCheck))
	{
		lineCount++;
	}
	if (lineCount != 29)
	{
		return false;
	}

	ifstream file(file_name);

	int coordCount = 0;

	if (file.is_open())
	{

		string line;
		for (int hall = 0; hall < HALL_SIZE; hall++)
		{
			for (int row = 0; row < ROW_SIZE; row++)
			{
				getline(file, line);
				if (line == "\n" || line.length() == 0)
				{
					getline(file, line);
				}
				stringstream stringCheck(line);
				stringstream ss(line);

				for (int col = 0; col < COL_SIZE; col++)
				{
					string coord;
					stringCheck >> coord;
					if (coord.size() > 1)
					{
						return false;
					}
					if (any_of(coord.begin(), coord.end(), ::isalpha))
					{
						return false;
					}

					int number;
					ss >> number;

					if (number == 0 || number == 1)
					{
						//cout << "[" << col << "][" << row << "][" << hall << "]=" << number << endl;
						maze_grid[col][row][hall] = number;
						path_grid[col][row][hall] = number;
						coordCount++;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}

	if (coordCount != 125)
	{
		return false;
	}

	if (maze_grid[4][4][4] == 0 || maze_grid[0][0][0] == 0)
	{
		return false;
	}

	return true;
}

string Pathfinder::toString() const
{
	stringstream ss;
	for (int hall = 0; hall < HALL_SIZE; hall++)
	{
		for (int row = 0; row < ROW_SIZE; row++)
		{
			for (int col = 0; col < COL_SIZE; col++)
			{
				ss << maze_grid[col][row][hall];
				if (col == COL_SIZE - 1)
				{
					continue;
				}
				else
				{
					ss << " ";
				}
			}
			ss << endl;
		}

		if (hall < HALL_SIZE - 1)
		{
			ss << endl;
		}
		else continue;

	}

	return ss.str();
}

vector<string> Pathfinder::solveMaze()
{
	solution.clear();
	find_maze_path(path_grid, STARTING_POS);

//	for (const auto& s : solution)
//	{
//		cout << s << endl;
//	}

	return solution;
}

bool Pathfinder::find_maze_path(int grid[COL_SIZE][ROW_SIZE][HALL_SIZE], Vector3 position)
{
	int c = position.x;
	int r = position.y;
	int h = position.z;

	solution.push_back("(" + to_string(c) + ", " + to_string(r) + ", " + to_string(h) + ")");

//	cout << "find_maze_path [" << c << "][" << r << "][" << h << "]" << endl;
//	cout << this->toString();

	if (position == ENDING_POS)
	{ // Victory check - Maze exit is always bottom end of row corner
		grid[c][r][h] = PATH;      // Cell is on path
		return true;               // and is maze exit.
	}
	else if (c < 0 ||
			 r < 0 ||
			 h < 0 ||
			 c >= COL_SIZE ||
			 r >= ROW_SIZE ||
			 h >= HALL_SIZE)
	{
		solution.pop_back();
		return false;     // Cell is out of bounds.
	}
	else if (grid[c][r][h] != GROUND)
	{
		solution.pop_back();
		return false;      // Cell is on barrier or dead end.
	}
	else if (grid[c][r][h] == WALL ||
			 grid[c][r][h] == TEMPORARY ||
			 grid[c][r][h] == PATH)
	{
		solution.pop_back();
		return false;
	}

	else
	{
		// Recursive case.
		// Attempt to find a path from each neighbor.
		// Tentatively mark cell as on path.
		grid[c][r][h] = PATH;

		if (find_maze_path(grid, position + Vector3::left()) ||
			find_maze_path(grid, position + Vector3::right())||
			find_maze_path(grid, position - Vector3::up()) 	 ||
			find_maze_path(grid, position - Vector3::down()) ||
			find_maze_path(grid, position - Vector3::back()) ||
			find_maze_path(grid, position - Vector3::forward()))
		{ //
			return true;
		}
		else
		{
			grid[c][r][h] = TEMPORARY;  // Dead end.
			solution.pop_back();
			return false;
		}
	}
}

void Pathfinder::createRandomMaze()
{
	int randomNum;
	for (int hall = 0; hall < HALL_SIZE; hall++)
	{
		for (int row = 0; row < ROW_SIZE; row++)
		{
			for (int col = 0; col < COL_SIZE; col++)
			{
				// Runs ROW_SIZE * COL_SIZE * HALL_SIZE times
				// 5*5*5 = 125 times
				randomNum = rand() % 2;
				maze_grid[col][row][hall] = randomNum;
				path_grid[col][row][hall] = randomNum;
			}
		}
	}
	maze_grid[0][0][0] = GROUND;
	maze_grid[COL_SIZE - 1][ROW_SIZE - 1][HALL_SIZE - 1] = GROUND;

	path_grid[0][0][0] = GROUND;
	path_grid[COL_SIZE - 1][ROW_SIZE - 1][HALL_SIZE - 1] = GROUND;

}