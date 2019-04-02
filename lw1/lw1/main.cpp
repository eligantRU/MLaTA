#include <iostream>
#include <optional>
#include <string>
#include <assert.h>
#include <list>
#include <set>

using namespace::std;

size_t Swap(size_t n)
{
	auto str = to_string(n);
	iter_swap(str.begin(), str.rbegin());
	return static_cast<size_t>(stoull(str));
}

void F(size_t n, size_t num, size_t max, set<size_t> & processed, list<size_t> & result)
{
	const auto was = n;

	if (n == num)
	{
		result.push_back(num);
		throw exception();
	}
	if ((n > max) || (processed.find(n) != processed.end()))
	{
		return;
	}

	processed.emplace_hint(processed.end(), n);

	try
	{
		F(static_cast<size_t>(stoull(to_string(n) + "1")), num, max, processed, result);
		F(2 * n, num, max, processed, result);
		F(Swap(n), num, max, processed, result);
	}
	catch (const exception &)
	{
		result.push_front(was);
		throw;
	}
}

optional<list<size_t>> Check(size_t num, size_t max)
{
	set<size_t> processed;
	list<size_t> result;
	try
	{
		F(1, num, max, processed, result);
	}
	catch (const exception &)
	{
		return result;
	}
	return nullopt;
}

void Print(const optional<list<size_t>> & result)
{
	if (!result)
	{
		cout << "No" << endl;
		return;
	}
	cout << "Yes" << endl;
	cout << result.value().size() << endl;
	for (const auto & el : result.value())
	{
		cout << el << " ";
	}
	cout << endl;
}

int main()
{
	{
		assert(Swap(123) == 321);
		assert(Swap(1230) == 231);
		assert(Check(3, 100) == nullopt);
	}
	{
		const auto bla = *Check(61, 100) == list<size_t>{1, 2, 4, 8, 16, 61};
		Print(Check(61, 100));
		assert(bla);
	}
	{
		const auto bla = *Check(1221, 1500) == list<size_t>{1, 11, 22, 221, 122, 1221};
		Print(Check(1221, 1500));
		assert(bla);
	}
	{
		const auto bla = *Check(22411, 23000) == list<size_t>{1, 2, 21, 211, 422, 224, 2241, 22411};
		Print(Check(22411, 1500));
		assert(bla);
	}
}
