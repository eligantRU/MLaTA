#include <algorithm>
#include <vector>
#include <array>

using namespace::std;

constexpr auto squareSide = 100;

struct Vec2
{
	int x = 0;
	int y = 0;

	Vec2 operator-(const Vec2& v) const
	{
		return { x - v.x, y - v.y };
	}
};

int Dot(const Vec2& lhs, const Vec2& rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y);
}

int CalculateRelativePosition(Vec2 p0, Vec2 p1, Vec2 p)
{
	Vec2 p0p1 = p1 - p0;
	Vec2 n{ -p0p1.y, p0p1.x };
	return Dot(p - p0, n);
}

template <class Comparator>
bool AreAllOf(const array<int, 4> & v, const Comparator& comparator)
{
	return all_of(v.begin(), v.end(), [&comparator](const auto & value) {
		return comparator(value, 0);
	});
}

bool HasIntersection(const pair<Vec2, Vec2> & square, const pair<Vec2, Vec2> & straight)
{
	const array<int, 4> v{
		CalculateRelativePosition(straight.first, straight.second, square.first - Vec2{squareSide, 0}),
		CalculateRelativePosition(straight.first, straight.second, square.first),
		CalculateRelativePosition(straight.first, straight.second, square.first - Vec2{0, squareSide}),
		CalculateRelativePosition(straight.first, straight.second, square.second)
	};
	return !(AreAllOf(v, std::less<int>()) || AreAllOf(v, std::greater<int>()));
}

size_t GetIntersectionCount(int n, int w, int e)
{
	pair<Vec2, Vec2> straight{ {0, w}, {100 * n, e} };

	vector<pair<Vec2, Vec2>> squares;
	squares.reserve(n * n);
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			squares.push_back({ { 100 * i, 100 * j }, { 100 * i - squareSide, 100 * j - squareSide } });
		}
	}
	return count_if(squares.begin(), squares.end(), [&straight](const auto & square) {
		return HasIntersection(square, straight);
	});
}
