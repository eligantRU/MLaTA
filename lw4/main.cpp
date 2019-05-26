// https://www.geeksforgeeks.org/longest-path-directed-acyclic-graph-set-2/
// https://www.sanfoundry.com/cpp-program-find-longest-path-dag/
// https://github.com/suman95/Critical-path-management/blob/master/critical_path_management.cpp

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <optional>
#include <stack>
#include <deque>

using namespace::std;
using EdgeType = map<pair<size_t, size_t>, size_t>;

void dfs(size_t vertexNum, vector<bool> & visited, vector<size_t> & result, const EdgeType & edges)
{
	visited[vertexNum] = true;

	EdgeType filteredEdges;
	for (const auto& bla : edges)
	{
		if (bla.first.first == vertexNum) filteredEdges[bla.first] = bla.second;
	}

	for (const auto& [edge, weight] : filteredEdges)
	{
		if (!visited[edge.second])
		{
			dfs(edge.second, visited, result, edges);
		}
	}

	result.push_back(vertexNum);
};

vector<size_t> TopologicalSort(const EdgeType& edges, size_t vertexCount)
{
	vector<size_t> result;
	result.reserve(vertexCount);
	vector<bool> visited(vertexCount, false);

	for (size_t vertexNum = 0; vertexNum < vertexCount; ++vertexNum)
	{
		if (!visited[vertexNum])
		{
			dfs(vertexNum, visited, result, edges);
		}
	}
	reverse(result.begin(), result.end());
	return result;
}

int main()
{
	size_t vertexCount, edgeCount, beginVertexNum, endVertexNum;
	cin >> vertexCount >> edgeCount >> beginVertexNum >> endVertexNum;

	EdgeType edges;
	for (size_t i = 0; i < edgeCount; ++i)
	{
		size_t beginEdge, endEdge, weight;
		cin >> beginEdge >> endEdge >> weight;
		edges[{beginEdge - 1, endEdge - 1}] = weight;
	}

	const auto sorted = TopologicalSort(edges, vertexCount);
	for (const auto& bla : sorted)
	{
		cout << bla << " ";
	}
	cout << endl;

	const auto s = 0;
	
	// Wikipedia
	/*auto V = sorted;
	vector<int> d(V.size(), -100);
	d[s] = 0;

	vector<optional<int>> p(V.size(), nullopt);*/

	const auto n = vertexCount;
	vector<int> indegree(n, 0);
	vector<int> LPT(n, 0);

	for (size_t i = 0; i < n; ++i)
	{
		for (const auto& [key, value] : edges)
		{
			++indegree[key.second];
		}
	}

	deque<int> q;
	for (size_t i = 0; i < n; ++i)
	{
		if (indegree[i] == 0)
		{
			q.push_back(i);
		}
	}

	while (!q.empty())
	{
		const auto j = q.front();
		q.pop_front();

		for (const auto& [key, value] : edges)
		{
			if (key.first != j)
			{
				continue;
			}
			
			--indegree[key.second];
			LPT[key.second] = max(LPT[key.second], 1 + LPT[key.first]);
			if (indegree[key.second] == 0)
			{
				q.push_back(key.second);
			}
		}
	}

	for (const auto bla : LPT)
	{
		cout << bla << " ";
	} // it's not working
	cout << endl;
}
