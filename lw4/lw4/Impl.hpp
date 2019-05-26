#include <algorithm>
#include <optional>
#include <vector>
#include <stack>
#include <list>

using namespace::std;

namespace
{

void DepthFirstSearch(size_t edgeBegin, vector<bool>& visited, list<size_t>& result, const vector<list<pair<size_t, int>>>& edges)
{
	visited[edgeBegin] = true;
	
	for (const auto& [edgeEnd, weight] : edges[edgeBegin])
	{
		if (!visited[edgeEnd])
		{
			DepthFirstSearch(edgeEnd, visited, result, edges);
		}
	}

	result.push_back(edgeBegin);
};

list<size_t> TopologicalSort(const vector<list<pair<size_t, int>>>& edges, size_t vertexCount)
{
	list<size_t> result;
	vector<bool> visited(vertexCount, false);

	for (size_t vertexNum = 0; vertexNum < vertexCount; ++vertexNum)
	{
		if (!visited[vertexNum])
		{
			DepthFirstSearch(vertexNum, visited, result, edges);
		}
	}
	return { result.rbegin(), result.rend() };
}

}

pair<vector<optional<int>>, vector<list<size_t>>> GetLongestPathsWithDistances(const vector<list<pair<size_t, int>>> & edges, size_t vertexCount, size_t vertexBeginNum)
{
	vector<optional<int>> longestDistances(vertexCount, nullopt);
	longestDistances[vertexBeginNum] = 0;

	vector<optional<size_t>> parent(vertexCount);

	const auto topologicalSortedVertices = TopologicalSort(edges, vertexCount);
		
	auto vertices(topologicalSortedVertices);
	while (!vertices.empty())
	{
		size_t u = vertices.front();
		vertices.pop_front();

		if (longestDistances[u])
		{
			for (const auto v : edges[u])
			{
				if (*longestDistances[v.first] > * longestDistances[u] - v.second)
				{
					parent[v.first] = u;
				}
				longestDistances[v.first] = min(*longestDistances[v.first], *longestDistances[u] - v.second);
			}
		}
	}

	vector<list<size_t>> longestPaths;
	for (size_t i = 0; i < vertexCount; ++i)
	{
		list<size_t> path;

		size_t wayPoint = i;
		while (parent[wayPoint])
		{
			path.push_front(wayPoint);
			wayPoint = *parent[wayPoint];
		}
		if (longestDistances[i])
		{
			path.push_front(vertexBeginNum);
		}
		longestPaths.push_back(path);
	}

	std::transform(longestDistances.begin(), longestDistances.end(), longestDistances.begin(), [](auto value) {
		return value ? make_optional(-*value) : nullopt;
	});

	return { longestDistances , longestPaths };
}
