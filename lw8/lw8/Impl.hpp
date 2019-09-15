#include <iostream>
#include <vector>

using namespace::std;

namespace
{

vector<vector<bool>> GenerateSquare(size_t squareSize, size_t onesCount)
{
	vector<vector<bool>> square(squareSize, vector<bool>(squareSize, false));
	for (size_t i = 0; i < squareSize; ++i)
	{
		for (size_t j = 0; j < squareSize; ++j)
		{
			if (onesCount-- == 0)
			{
				goto forced_return;
			}
			square[i][j] = true;
		}
	}

forced_return:
	return square;
}

}

vector<vector<bool>> GenerateTable(size_t tableSize, size_t squareSize, size_t onesCount)
{
	const auto square = GenerateSquare(squareSize, onesCount);
	vector<vector<bool>> table(tableSize, vector<bool>(tableSize, false));
	for (size_t i = 0; i < tableSize; ++i)
	{
		for (size_t j = 0; j < tableSize; ++j)
		{
			table[i][j] = square[i % squareSize][j % squareSize];
		}
	}
	return table;
}
