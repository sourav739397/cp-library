/**
 * Description: Shortest Path w/ negative edge weights
 * Source: Benq
 * Verification:
 * https://open.kattis.com/problems/shortestpath3
 */

struct BellmanFord
{
	int N;
	vector<int64_t> dist;
	vector<vector<int>> adj;
	vector<array<int, 3>> ed;
	BellmanFord(int _N)
	{
		N = _N;
		adj.resize(N);
		dist.resize(N, INT64_MAX);
	}
	void ae(int u, int v, int w)
	{
		adj[u].push_back(v);
		ed.push_back({u, v, w});
	}
	void genBad(int u)
	{
		if (dist[u] == INT64_MIN)
			return;
		dist[u] = INT64_MIN;
		for (auto &v : adj[u])
			genBad(v);
	}
	void genDist(int src)
	{
		dist[src] = 0;
		for (int i = 0; i < N; i++)
		{
			for (auto &[u, v, w] : ed)
			{
				if (dist[u] < INT64_MAX)
				{
					dist[v] = min(dist[v], dist[u] + w);
				}
			}
		}
		for (auto &[u, v, w] : ed)
		{
			if (dist[u] < INT64_MAX && dist[v] > dist[u] + w)
				genBad(v);
		}
	}
};
