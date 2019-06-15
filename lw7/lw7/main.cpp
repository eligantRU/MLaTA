/*
17.2. Инверсии 2 (7)
Задан вектор инверсий перестановки X = (X 1 , X 2 , …, X N ) чисел от до N (1 <= N <= 500000).
Требуется найти саму перестановку.

Егоров Никита, ПС-21
*/

#include <fstream>
#include <chrono>

#include "Impl.hpp"

using namespace::std;

template <class T>
auto MeasureTime(T && fn)
{
	auto begin = chrono::high_resolution_clock::now();
	fn();
	auto end = chrono::high_resolution_clock::now();
	return (end - begin);
}

int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");

	auto t = MeasureTime([&] {
		size_t numsCount;
		input >> numsCount;

		vector<size_t> inversion(numsCount, 0);
		for (size_t i = 0; i < numsCount; ++i)
		{
			input >> inversion[i];
		}
		for (const auto value : GetPermutationByInversion(inversion))
		{
			output << value << " ";
		}
		output << endl;
	});
	cerr << "runtime = " << chrono::duration_cast<chrono::milliseconds>(t).count() << " ms" << endl;
}
