/*
2.8. Калькулятор (7)
Одна фирма выпускает в продажу странные калькуляторы. Они могут выполнять лишь три
операции:
* ввести число 1;
* удвоить текущее число;
* поменять в текущем числе первую и последнюю цифры.
Калькулятор умеет работать лишь с целыми числами от 1 до L (1 ≤ L ≤ 10 5 ). Незначащие нули в
начале числа отбрасываются. Написать программу, которая проверяет, можно ли на данном
калькуляторе получить число N (1 ≤ N ≤ 10 5 ). Если это возможно, выдать самую короткую
последовательность преобразований.
Ввод. В единственной строке находятся через пробел значения число L и N.
Вывод. В первой строке вывести Yes или No. Если значение N достижимо, во второй строке
выдать количество значений в цепочке преобразований от 1 до N, а в третьей строке через пробел
сами эти значения.

Егоров Никита, ПС-21
C++17
*/

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
