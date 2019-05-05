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

	size_t num, max;
	input >> max >> num;

	const auto dt = MeasureTime([&]() {
		Print(Check(num, max), output);
	});
	cerr << "runtime: " << chrono::duration_cast<chrono::milliseconds>(dt).count() << " ms" << std::endl;
}
