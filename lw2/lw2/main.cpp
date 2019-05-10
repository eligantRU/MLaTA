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
