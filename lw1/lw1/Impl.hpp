#include <algorithm>
#include <optional>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <set>

using namespace::std;

size_t Swap(size_t n)
{
	auto str = to_string(n);
	iter_swap(str.begin(), str.rbegin());
	return static_cast<size_t>(stoull(str));
}

list<size_t> ToList(const deque<size_t>& st)
{
	return { st.begin(), st.end() };
}

void F(size_t n, size_t num, size_t max, size_t last, deque<size_t> & st, set<size_t> & processed, vector<deque<size_t>> & results)
{
	if ((n > max) || (processed.find(n) != processed.end()))
	// if ((n > max) || find(st.begin(), st.end(), n) != st.end())
	{
		return;
	}
	processed.emplace_hint(processed.end(), n);
	st.push_back(n);

	if (n == num)
	{
		results.push_back(st);
		return;
	}

	if (true)
	{
		cerr << " >> " << last << " -> " << n <<  " <<" << endl;
		cerr << static_cast<size_t>(stoull(to_string(n) + "1")) << endl;
		cerr << 2 * n << endl;
		cerr << Swap(n) << endl;
		cerr << endl;
	}

	F(static_cast<size_t>(stoull(to_string(n) + "1")), num, max, n, st, processed, results);
	F(2 * n, num, max, n, st, processed, results);
	F(Swap(n), num, max, n, st, processed, results);

	st.pop_back();
}

optional<list<size_t>> Check(size_t num, size_t max)
{
	if (num > max)
	{
		return nullopt;
	}

	set<size_t> processed;
	deque<size_t> st;
	vector<deque<size_t>> results;
	F(1, num, max, 1, st, processed, results);

	sort(results.begin(), results.end(), [](const auto & lhs, const auto & rhs) {
		return lhs.size() < rhs.size();
	});
	return results.empty()
		? nullopt
		: make_optional(ToList(results.front()));
}

void Print(const optional<list<size_t>>& result)
{
	if (!result)
	{
		cout << "No" << endl;
		return;
	}
	cout << "Yes" << endl;
	cout << result.value().size() << endl;
	for (const auto& el : result.value())
	{
		cout << el << " ";
	}
	cout << endl;
}
