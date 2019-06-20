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
	{
		auto tmp(base);

		m_crutch = !(tmp.size() % 4) ? 0 : 4 - (tmp.size() % 4);
		tmp.insert(tmp.begin(), m_crutch, 0);
		m_tree = vector<T>(4 * tmp.size(), 0);
		BuildImpl(tmp, 1, 0, tmp.size() - 1);
		m_size = tmp.size();
	}

	T Sum(size_t left, size_t right) const
	{
		//return SumImpl(1, 0, m_size, left + m_crutch, right + m_crutch);

		T result = 0;
		for (size_t pos = left + m_crutch; pos < right + m_crutch; ++pos)
		{
			result += Get(1, 0, m_size, pos + 1);
		}
		return result;
	}

	void Add(size_t left, size_t right, T value)
	{
		AddImpl(1, 0, m_size, left + m_crutch, right + m_crutch, value);
	}

	void Print(ostream & strm = cout) const
	{
		for (size_t pos = m_crutch; pos < m_size; ++pos)
		{
			strm << Get(1, 0, m_size, pos + 1) << " ";
		}
		strm << endl;
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

	void AddImpl(size_t v, size_t left, size_t right, size_t l, size_t r, T addValue)
	{
		if (l > r)
		{
			return;
		}

		if (l == left && right == r)
		{
			m_tree[v] += addValue;
		}
		else
		{
			const auto middle = (left + right) / 2;
			AddImpl(2 * v, left, middle, l, min(r, middle), addValue);
			AddImpl(2 * v + 1, middle + 1, right, max(l, middle + 1), r, addValue);
		}
	}

	/*T SumImpl(size_t v, size_t left, size_t right, size_t l, size_t r) const
	{
		if (begin > end)
			return 0;
		if (begin == leftLimit && end == rightLimit)
			return m_tree[i];

		int half = (leftLimit + rightLimit) / 2;
		int diff = m_treeDiffs[i] * (end - begin + 1);
		return Sum(i * 2, begin, std::min(end, half), leftLimit, half) +
			Sum(i * 2 + 1, std::max(begin, half + 1), end, half + 1, rightLimit) + diff;
	}*/

	T Get(size_t v, size_t left, size_t right, size_t pos) const
	{
		if (left == right)
		{
			return m_tree[v];
		}
		const auto middle = (left + right) / 2;
		return (pos <= middle)
			? m_tree[v] + Get(2 * v, left, middle, pos)
			: m_tree[v] + Get(2 * v + 1, middle + 1, right, pos);
	}

	vector<T> m_tree;
	size_t m_crutch = 0;
	size_t m_size = 0;
};
