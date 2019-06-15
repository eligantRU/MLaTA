/*
15.6 Касса
Написать программу для игры касса, рассмотренной в настоящем разделе.
Ввод из файла INPUT.TXT. В единственной строке находится количество монет N (N  200).
Вывод в файл OUTPUT.TXT. Вывести 1, если при правильной игре выигрывает первый игрок,
либо 2 – если выигрывает второй.

Егоров Никита, ПС-21
*/

#include <fstream>

#include "Impl.hpp"

int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");

	size_t N;
	input >> N;
	output << (IsFirstWinner(N) ? "1" : "2") << endl;
}
