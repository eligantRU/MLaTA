/*
19.16. Простые числа (3)
Найти сумму простых чисел, расположенных между N и K (0 < N ≤ K ≤ 10^6 ), включая эти числа.
Ввод. В первой строке файла INPUT.TXT содержатся через пробел натуральные числа N и K.
Вывод. Вывести в файл OUTPUT.TXT одно число - сумму простых чисел, расположенных
между N и K.

Егоров Никита, ПС-21
*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <fstream>
#include <vector>
#include <cctype>
#include <list>

using namespace::std;

list <uint32_t> GeneratePrimeNumbersSet(uint32_t upperBound)
{
	vector<bool> nums(upperBound + 1, true);

	for (uint32_t i = 2; i * i <= upperBound; ++i)
	{
		if (nums[i])
		{
			for (uint32_t j = i * i; j <= upperBound; j += 2 * i)
			{
				nums[j] = false;
			}
		}
	}

	list<uint32_t> primes;
	if (upperBound >= 2)
	{
		primes.emplace_front(2);
	}
	for (unsigned i = 3; i <= upperBound; i += 2)
	{
		if (nums[i])
		{
			primes.emplace_back(i);
		}
	}
	return primes;
}

bool IsInRange(uint32_t value, uint32_t lowerBound, uint32_t upperBound)
{
	return (lowerBound <= value) && (value <= upperBound);
}

int main(int argc, char* argv[])
{
	ifstream input("input.txt");
	ofstream output("output.txt");

	uint32_t lowerBound, upperBound;
	input >> lowerBound >> upperBound;

	auto primes = GeneratePrimeNumbersSet(upperBound);
	auto it = remove_if(primes.begin(), primes.end(), [lowerBound, upperBound](uint32_t prime) {
		return !IsInRange(prime, lowerBound, upperBound);
	});
	primes.erase(it, primes.end());
	output << accumulate(primes.begin(), primes.end(), (uint64_t)0) << endl;
}
