#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace::std;

template <class T>
class SegmentTree
{
public:
	explicit SegmentTree(const vector<T> & base)
		:m_tree(vector<T>(4 * base.size(), 0))
		,m_diffs(vector<T>(4 * base.size(), 0))
		,m_size(base.size())
	{
		BuildImpl(base, 1, 0, m_size - 1);
	}

	T Sum(size_t left, size_t right) const
	{
		return SumImpl(1, 0, m_size - 1, left, right - 1);
	}

	void Add(size_t left, size_t right, T value)
	{
		AddImpl(1, 0, m_size - 1, left, right - 1, value);
	}

	void Print(ostream& strm = cout) const
	{
		for (size_t pos = 0; pos < m_size; ++pos)
		{
			strm << Get(pos) << " ";
		}
		strm << endl;
	}

	T Get(size_t pos) const
	{
		return Sum(pos, pos + 1);
	}

private:
	void BuildImpl(const vector<T> & base, size_t v, size_t left, size_t right)
	{
		if (left == right)
		{
			m_tree[v] = base[left];
		}
		else
		{
			const auto middle = (left + right) / 2;
			BuildImpl(base, 2 * v, left, middle);
			BuildImpl(base, 2 * v + 1, middle + 1, right);
		}
	}

	void AddImpl(size_t v, size_t left, size_t right, size_t l, size_t r, int64_t value)
	{
		if (l > r)
		{
			return;
		}

		m_tree[v] += value * ((int64_t)r - l + 1);
		if (left == l && right == r)
		{
			m_diffs[v] += value;
			return;
		}

		const auto middle = (left + right) / 2;
		AddImpl(2 * v, left, middle, l, min(r, middle), value);
		AddImpl(2 * v + 1, middle + 1, right, max(l, middle + 1), r, value);
	}

	T SumImpl(size_t v, size_t left, size_t right, size_t l, size_t r) const
	{
		if (l > r)
		{
			return 0;
		}

		if (l == left && r == right)
		{
			return m_tree[v];
		}

		const auto middle = (left + right) / 2;
		const auto diff = m_diffs[v] * ((int64_t)r - l + 1);
		return SumImpl(2 * v, left, middle, l, min(r, middle))
			+ SumImpl(2 * v + 1, middle + 1, right, max(l, middle + 1), r)
			+ diff;
	}

	vector<T> m_tree;
	vector<T> m_diffs;
	size_t m_size = 0;
};
