#include <unordered_set>
#include <algorithm>
#include <optional>
#include <iostream>
#include <string>
#include <vector>

using namespace::std;

size_t Swap(size_t n)
{
	auto str = to_string(n);
	iter_swap(str.begin(), str.rbegin());
	return static_cast<size_t>(stoull(str));
}

bool IsContains(const unordered_set<size_t>& container, size_t value)
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

void InvalidateResults(vector<list<size_t>> & results, const vector<pair<size_t, size_t>> & l, size_t num, const vector<vector<pair<size_t, size_t>>> & stateHistory)
{
	if (IsContains(l, num))
	{
		size_t value = num;
		list<size_t> res = { value };
		for (size_t i = stateHistory.size() - 1; i >= 1; --i)
		{
			const auto parentId = GetParentId(stateHistory[i], value);
			const auto parent = stateHistory[i - 1][parentId];
			res.push_front(parent.first);
			value = parent.first;
		}
		results.push_back(res);
	}
}

vector<list<size_t>> F(size_t num, size_t max)
{
	vector<list<size_t>> results;
	if (num == 1)
	{
		results.emplace_back(1, 1);
		return results;
	}

	vector<pair<size_t, size_t>> state = { {1, 0} };
	vector<vector<pair<size_t, size_t>>> stateHistory = { state };
	unordered_set<size_t> totalProcessed = { 1 };

	unordered_set<size_t> processed;
	while (!state.empty())
	{
		totalProcessed.insert(processed.begin(), processed.end());
		vector<pair<size_t, size_t>> nextState;
		nextState.reserve(3 * state.size());

		for (size_t i = 0; i < state.size(); ++i)
		{
			const auto [value, count] = state[i];

			if (const auto future = static_cast<size_t>(stoull(to_string(value) + "1")); (future <= max) && !IsContains(processed, future))
			{
				nextState.emplace_back(future, i);
				processed.emplace(future);
			}
			if (const auto future = 2 * value; (future <= max) && !IsContains(totalProcessed, future))
			{
				nextState.emplace_back(future, i);
				processed.emplace(future);
			}
			if (const auto future = Swap(value); (future <= max) && !IsContains(totalProcessed, future))
			{
				nextState.emplace_back(future, i);
				processed.emplace(future);
			}
		}
		swap(state, nextState);
		stateHistory.push_back(state);

		InvalidateResults(results, state, num, stateHistory);
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

void Print(const optional<list<size_t>>& result, ostream & strm = cout)
{
	if (!result)
	{
		strm << "No" << endl;
		return;
	}
	strm << "Yes" << endl;
	strm << result.value().size() << endl;
	for (const auto& el : result.value())
	{
		strm << el << " ";
	}
	strm << endl;
}
