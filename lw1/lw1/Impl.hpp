#include <algorithm>
#include <optional>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>

using namespace::std;

size_t Swap(size_t n)
{
	auto str = to_string(n);
	iter_swap(str.begin(), str.rbegin());
	return static_cast<size_t>(stoull(str));
}

void PrintImpl(const vector<pair<size_t, size_t>>& st)
{
	string strSt;
	for (const auto & [value, parent] : st)
	{
		strSt += to_string(value) + " ";
	}
	cerr << " >> " << strSt << endl;
}

bool IsContains(const set<size_t>& container, size_t value)
{
	return find(container.cbegin(), container.cend(), value) != container.cend();
}

bool IsContains(const vector<pair<size_t, size_t>>& container, size_t value)
{
	return find_if(container.cbegin(), container.cend(), [value](const auto & bla) {
		return bla.first == value;
	}) != container.cend();
}

size_t GetParentId(const vector<pair<size_t, size_t>>& container, size_t value)
{
	const auto it = find_if(container.cbegin(), container.cend(), [value](const auto & bla) {
		return bla.first == value;
	});
	return it->second;
}

vector<list<size_t>> F(size_t num, size_t max)
{
	vector<list<size_t>> results;
	if (num == 1)
	{
		results.emplace_back(1, 1);
		return results;
	}

	vector<pair<size_t, size_t>> l = { {1, 0} };
	vector<vector<pair<size_t, size_t>>> history = { l };
	set<size_t> processed = { 1 };

	set<size_t> tmpProcessed;
	while (!l.empty())
	{
		processed.insert(tmpProcessed.begin(), tmpProcessed.end());
		vector<pair<size_t, size_t>> tmp;
		for (size_t i = 0; i < l.size(); ++i)
		{
			const auto [value, count] = l[i];

			if (const auto future = static_cast<size_t>(stoull(to_string(value) + "1")); (future <= max) && !IsContains(processed, future))
			{
				tmp.emplace_back(future, i);
				tmpProcessed.emplace(future);
			}
			if (const auto future = 2 * value; (future <= max) && !IsContains(processed, future))
			{
				tmp.emplace_back(future, i);
				tmpProcessed.emplace(future);
			}
			if (const auto future = Swap(value); (future <= max) && !IsContains(processed, future))
			{
				tmp.emplace_back(future, i);
				tmpProcessed.emplace(future);
			}
		}
		// PrintImpl(tmp);
		swap(l, tmp);
		history.push_back(l);

		if (IsContains(l, num))
		{
			size_t value = num;
			list<size_t> res = { value };
			for (size_t i = history.size() - 1; i >= 1; --i)
			{
				const auto parentId = GetParentId(history[i], value);
				const auto parent = history[i - 1][parentId];
				res.push_front(parent.first);
				value = parent.first;
			}
			results.push_back(res);
		}
	}
	return results;
}

optional<list<size_t>> Check(size_t num, size_t max)
{
	if (num > max)
	{
		return nullopt;
	}

	vector<list<size_t>> results = F(num, max);
	sort(results.begin(), results.end(), [](const auto & lhs, const auto & rhs) {
		return lhs.size() < rhs.size();
	});
	return results.empty()
		? nullopt
		: make_optional(results.front());
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
