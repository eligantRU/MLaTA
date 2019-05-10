/*
11.2. Прямая и квадраты (5)
В прямоугольной декартовой системе координат прямая задана двумя принадлежащими ей
точками (0, W) и (100N, E) (1 <= N <= 100, 0 <= W, E <= 100N). Также заданы N^2  квадратов со
сторонами, параллельными осям координат. Квадрат S i, j  имеет координаты углов (100i, 100j) и
(100i - 100, 100j - 100), где i, j = 1, 2, ..., N. Требуется найти количество квадратов, имеющих
общую точку с прямой.
Ввод из файла INPUT.TXT. В первой строке находятся три целых числа, N, W и E, разделенные
пробелами.
Вывод в файл OUTPUT.TXT. Вывести одно число - количество квадратов.

Егоров Никита, ПС-21
C++17
*/

#include <iostream>
#include <fstream>
#include <chrono>

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

	int n, w, e;
	input >> n >> w >> e;

	const auto dt = MeasureTime([&]() {
		output << GetIntersectionCount(n, w, e) << endl;
	});
	cerr << "runtime: " << chrono::duration_cast<chrono::milliseconds>(dt).count() << " ms" << std::endl;
}
