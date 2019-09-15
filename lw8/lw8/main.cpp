/*
10.13. Квадрат в квадрате (5)
Требуется в каждую клетку квадратной таблицы размером N × N поставить ноль или единицу
так, чтобы в максимальном количестве квадратов размера K×K было ровно S единиц.
Ввод из файла INPUT.TXT. Единственная строка содержит три числа: N, K, S (1 <= N <= 500,
1 <= K <= N, 0 <= S <= K^2 ).
Вывод в файл OUTPUT.TXT. В первую строку необходимо вывести максимальное число
квадратов из нулей и единиц размера K×K, в каждом из которых ровно S единиц. В следующих N
строках вывести по N элементов в строке полученную таблицу из нулей и единиц. Если решений
несколько, то вывести любое из них.

Егоров Никита, ПС-21
*/

#include <fstream>

#include "Impl.hpp"

int main()
{
	size_t tableSize;
	size_t squareSize;
	size_t onesCount;
	ifstream("input.txt") >> tableSize >> squareSize >> onesCount;

	ofstream output("output.txt");
	output << (tableSize - squareSize + 1) * (tableSize - squareSize + 1) << endl;
	const auto table = GenerateTable(tableSize, squareSize, onesCount);
	for (const auto& row : table)
	{
		for (const auto val : row)
		{
			output << val << " ";
		}
		output << endl;
	}
}
