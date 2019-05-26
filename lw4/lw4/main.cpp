/*
12.14. Максимальный путь 2 (8)
Имеется взвешенный ориентированный ациклический граф. Найти максимальный путь,
используя топологическую сортировку.
Ввод из файла INPUT.TXT. Первая строка входного файла INPUT.TXT содержит 4 числа: N -
количество вершин графа (3 ≤ N ≤ 2000), M – дуг (3 ≤ M ≤ 2000000), A – номер начальной вершины
и B – номер конечной вершины. В следующих M строках по 3 числа, задающих дуги: начало дуги,
конец дуги, длина (вес).
Вывод в файл OUTPUT.TXT. В первую строку вывести максимальную длину пути, во вторую
строку через пробел – вершины максимального пути. Если решений несколько, вывести любое из
них. Если пути нет, выдать No.

Егоров Никита, ПС-21
C++17
*/

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

#include "Impl.hpp"

template <class T>
auto MeasureTime(T&& fn)
{
	const auto begin = chrono::high_resolution_clock::now();
	fn();
	const auto end = chrono::high_resolution_clock::now();
	return (end - begin);
}

int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");

	size_t verticesCount, edgesCount, vertexBeginNum, vertexEndNum;
	input >> verticesCount >> edgesCount >> vertexBeginNum >> vertexEndNum;
	--vertexBeginNum;
	--vertexEndNum;

	vector<list<pair<size_t, int>>> edges(verticesCount);
	for (size_t i = 0; i < edgesCount; ++i)
	{
		size_t beginEdge, endEdge;
		int weight;
		input >> beginEdge >> endEdge >> weight;
		edges[beginEdge - 1].emplace_back(endEdge - 1, weight);
	}
	
	vector<optional<int>> longestDistances;
	vector<list<size_t>> longestPaths;
	const auto dt = MeasureTime([&]() {
		auto [distances, paths] = GetLongestPathsWithDistances(edges, verticesCount, vertexBeginNum);
		std::swap(longestDistances, distances);
		std::swap(longestPaths, paths);
	});
	cerr << "runtime: " << chrono::duration_cast<chrono::milliseconds>(dt).count() << " ms" << std::endl;

	if (longestDistances[vertexEndNum])
	{
		output << to_string(*longestDistances[vertexEndNum]) << endl;
		for (const auto point : longestPaths[vertexEndNum])
		{
			output << point + 1 << " ";
		}
		output << endl;
	}
	else
	{
		output << "No" << endl;
	}
}
