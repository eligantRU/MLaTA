#pragma once

#include <iostream>
#include <numeric>
#include <vector>

using namespace::std;

class FenwickTree
{
public:
	FenwickTree(const vector<size_t> & values)
		:m_tree(values.size() + 1, 0)
	{
		for (size_t i = 0; i < values.size(); ++i)
		{
			Add(i + 1, values[i]);
		}
	}

	void Add(int pos, int value)
	{
		while (pos < m_tree.size())
		{
			m_tree[pos] += value;
			pos = pos | (pos + 1);
		}
	}

	int Rsq(int pos) const
	{
		if (pos == -1) return 0;

		int res = 0;
		while (pos >= 0)
		{
			res += m_tree[pos];
			pos = (pos & (pos + 1)) - 1;
			if (pos == -1)
			{
				pos = -1;
			}
		}
		return res;
	}

	int Rsq(int left, int right) const
	{
		return Rsq(right) - Rsq(left - 1);
	}

	void Update(int pos, int value)
	{
		Add(pos, value - Rsq(pos, pos));
	}

	void Print(ostream & strm = cout) const
	{
		for (size_t i = 1; i < m_tree.size(); ++i)
		{
			strm << Rsq(i) - Rsq(i - 1) << " ";
		}
		strm << endl;
	}

private:
	vector<size_t> m_tree;
};

template <class T>
size_t BinarySearch(size_t left, size_t right, size_t value, T && comp)
{
	const auto fn = [](size_t left, size_t right, size_t value, T && comp) {
		while (left <= right)
		{
			const auto middle = left + (right - left) / 2;
			if (comp(middle) == value)
			{
				return middle;
			}
			else if (comp(middle) < value)
			{
				left = middle + 1;
			}
			else
			{
				right = middle - 1;
			}
		}
		throw exception("Cannot found value using binarySearch");
	};
	size_t i = fn(left, right, value, std::move(comp));
	while (comp(i - 1) == value)
	{
		--i;
	}
	return i;
}

vector<size_t> GetPermutationByInversion(const vector<size_t> & inversion)
{
	vector<size_t> permutation(inversion.size(), 0);
	FenwickTree tree(vector<size_t>(inversion.size(), 1));

	auto processingIndex = inversion.size() - 1;
	while (true)
	{
		const auto value = inversion[processingIndex];

		const auto pos = BinarySearch(0, inversion.size(), 1 + processingIndex - value, [&tree](size_t pos) {
			return tree.Rsq(pos);
		});
		tree.Update(pos, 0);
		permutation[processingIndex] = pos;
		if (processingIndex-- == 0) break;
	}
	return permutation;
}
