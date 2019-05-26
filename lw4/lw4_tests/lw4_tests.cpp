#include "stdafx.h"

#include "../lw4/Impl.hpp"

BOOST_AUTO_TEST_SUITE(lw4)

BOOST_AUTO_TEST_CASE(CriticalPath_)
{
	{
		constexpr size_t verticesCount = 6;
		constexpr size_t vertexBeginNum = 1;
		
		vector<list<pair<size_t, int>>> edges(verticesCount);
		edges[0].emplace_back(1, 5);
		edges[0].emplace_back(2, 3);
		edges[1].emplace_back(3, 6);
		edges[1].emplace_back(2, 2);
		edges[2].emplace_back(4, 4);
		edges[2].emplace_back(5, 2);
		edges[2].emplace_back(3, 7);
		edges[3].emplace_back(5, 1);
		edges[3].emplace_back(4, -1);
		edges[4].emplace_back(5, -2);

		const vector<optional<int>> expectedDistances = { nullopt, 0, 2, 9, 8, 10 };

		const auto [longestDistances, longestPaths] = GetLongestPathsWithDistances(edges, verticesCount, vertexBeginNum);
		BOOST_CHECK(longestDistances == expectedDistances);
	}

	{
		constexpr size_t verticesCount = 5;
		constexpr size_t vertexBeginNum = 0;
		constexpr size_t vertexEndNum = 4;

		vector<list<pair<size_t, int>>> edges(verticesCount);
		edges[0].emplace_back(1, 3);
		edges[0].emplace_back(2, 2);
		edges[2].emplace_back(1, 2);
		edges[2].emplace_back(3, 1);
		edges[3].emplace_back(1, 4);
		edges[1].emplace_back(4, 5);

		const vector<optional<int>> expectedDistances = { 0, 7, 2, 3, 12 };

		const auto [longestDistances, longestPaths] = GetLongestPathsWithDistances(edges, verticesCount, vertexBeginNum);
		BOOST_CHECK(longestDistances == expectedDistances);
		BOOST_CHECK(*longestDistances[vertexEndNum] == 12);
	}

	{
		constexpr size_t verticesCount = 4;

		vector<list<pair<size_t, int>>> edges(verticesCount);
		edges[0].emplace_back(1, 5);
		edges[0].emplace_back(3, 7);
		edges[1].emplace_back(2, 4);
		edges[3].emplace_back(1, 2);
		edges[3].emplace_back(2, 3);

		{
			constexpr size_t vertexBeginNum = 0;
			constexpr size_t vertexEndNum = 2;

			const vector<optional<int>> expectedDistances = { 0, 9, 13, 7 };
			const list<size_t> expectedPath = { 0, 3, 1, 2 };

			const auto [longestDistances, longestPaths] = GetLongestPathsWithDistances(edges, verticesCount, vertexBeginNum);
			BOOST_CHECK(longestDistances == expectedDistances);
			BOOST_CHECK(*longestDistances[vertexEndNum] == 13);
			BOOST_CHECK(longestPaths[vertexEndNum] == expectedPath);
		}
		{
			constexpr size_t vertexBeginNum = 1;
			constexpr size_t vertexEndNum = 0;

			const vector<optional<int>> expectedDistances = { nullopt, 0, 4, nullopt };

			const auto [longestDistances, longestPaths] = GetLongestPathsWithDistances(edges, verticesCount, vertexBeginNum);
			BOOST_CHECK(longestDistances == expectedDistances);
			BOOST_CHECK(!longestDistances[vertexEndNum]);
		}
	}

	{
		constexpr size_t verticesCount = 8;
		constexpr size_t vertexBeginNum = 0;
		constexpr size_t vertexEndNum = 7;

		vector<list<pair<size_t, int>>> edges(verticesCount);
		edges[0].emplace_back(1, 1);
		edges[0].emplace_back(2, 1);
		edges[0].emplace_back(3, 1);
		edges[0].emplace_back(4, 1);
		edges[0].emplace_back(5, 1);
		edges[0].emplace_back(6, 1);
		edges[0].emplace_back(7, 1);
		edges[1].emplace_back(2, 1);
		edges[1].emplace_back(3, 1);
		edges[1].emplace_back(4, 1);
		edges[1].emplace_back(5, 1);
		edges[1].emplace_back(6, 1);
		edges[1].emplace_back(7, 1);
		edges[2].emplace_back(3, 1);
		edges[2].emplace_back(4, 1);
		edges[2].emplace_back(5, 1);
		edges[2].emplace_back(6, 1);
		edges[2].emplace_back(7, 1);
		edges[3].emplace_back(4, 1);
		edges[3].emplace_back(5, 1);
		edges[3].emplace_back(6, 1);
		edges[3].emplace_back(7, 1);
		edges[4].emplace_back(5, 1);
		edges[4].emplace_back(6, 1);
		edges[4].emplace_back(7, 1);
		edges[5].emplace_back(6, 1);
		edges[5].emplace_back(7, 1);
		edges[6].emplace_back(7, 1);

		const vector<optional<int>> expectedDistances = { 0, 1, 2, 3, 4, 5, 6, 7 };
		const list<size_t> expectedPath = { 0, 1, 2, 3, 4, 5, 6, 7 };

		const auto [longestDistances, longestPaths] = GetLongestPathsWithDistances(edges, verticesCount, vertexBeginNum);
		BOOST_CHECK(longestDistances == expectedDistances);
		BOOST_CHECK(*longestDistances[vertexEndNum] == 7);
		BOOST_CHECK(longestPaths[vertexEndNum] == expectedPath);
	}

	{
		constexpr size_t verticesCount = 8;
		constexpr size_t vertexBeginNum = 4;
		constexpr size_t vertexEndNum = 3;

		vector<list<pair<size_t, int>>> edges(verticesCount);
		edges[1].emplace_back(6, 4);
		edges[2].emplace_back(5, 10);
		edges[4].emplace_back(7, 6);
		edges[7].emplace_back(6, 5);
		edges[5].emplace_back(3, 3);
		edges[4].emplace_back(1, 3);
		edges[0].emplace_back(3, 2);
		edges[6].emplace_back(0, 6);
		edges[5].emplace_back(0, 2);
		edges[6].emplace_back(5, 5);
		edges[4].emplace_back(2, 2);

		const vector<optional<int>> expectedDistances = { 18, 3, 2, 20, 0, 16, 11, 6 };
		const list<size_t> expectedPath = { 4, 7, 6, 5, 0, 3 };

		const auto [longestDistances, longestPaths] = GetLongestPathsWithDistances(edges, verticesCount, vertexBeginNum);
		BOOST_CHECK(longestDistances == expectedDistances);
		BOOST_CHECK(longestDistances[vertexEndNum] == 20);
		BOOST_CHECK(longestPaths[vertexEndNum] == expectedPath);
	}

	{
		constexpr size_t verticesCount = 10;
		constexpr size_t vertexBeginNum = 5;
		constexpr size_t vertexEndNum = 1;

		vector<list<pair<size_t, int>>> edges(verticesCount);
		edges[3].emplace_back(6, 3);
		edges[3].emplace_back(7, 6);
		edges[3].emplace_back(9, 1);
		edges[7].emplace_back(5, 3);
		edges[6].emplace_back(0, 5);
		edges[6].emplace_back(5, 2);
		edges[9].emplace_back(8, 8);
		edges[5].emplace_back(8, 3);
		edges[5].emplace_back(4, 5);
		edges[0].emplace_back(4, 2);
		edges[8].emplace_back(1, 5);
		edges[4].emplace_back(1, 4);
		edges[4].emplace_back(2, 8);

		const vector<optional<int>> expectedDistances = { nullopt, 9, 13, nullopt, 5, 0, nullopt, nullopt, 3, nullopt };
		const list<size_t> expectedPath = { 5, 4, 1 };

		const auto [longestDistances, longestPaths] = GetLongestPathsWithDistances(edges, verticesCount, vertexBeginNum);
		BOOST_CHECK(longestDistances == expectedDistances);
		BOOST_CHECK(*longestDistances[vertexEndNum] == 9);
		BOOST_CHECK(longestPaths[vertexEndNum] == expectedPath);
	}
}

BOOST_AUTO_TEST_SUITE_END()
