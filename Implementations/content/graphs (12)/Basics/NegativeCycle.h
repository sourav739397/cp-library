/**
 * Description: use Bellman-Ford (make sure no underflow)
 * Source: https://cp-algorithms.com/graph/finding-negative-cycle-in-graph.html
 * Verification: https://cses.fi/problemset/task/1197/
 */

vector<int> NegativeCycle(int N, vector<array<int, 3>> &ed) {
	vector<int64_t> dist(N);
	vector<int> p(N);
	int x = -1;
	for (int i = 0; i < N; i++) {
		x = -1;
		for (auto &[u, v, w] : ed) {
			if (dist[v] > dist[u]+w) {
				dist[v] = dist[u]+w;
				p[v] = u, x = v;
			}
		}
		if (x == -1) return {};
	}

	for (int i = 0; i < N; i++) x = p[x]; // enter cycle
	vector<int> cyc{x};
	while (p[cyc.back()] != x) cyc.push_back(p[cyc.back()]);
	cyc.push_back(x); // complete cycle
	ranges::reverse(cyc);
	return cyc;
}

/**
Explanation:

If we follow the links back from t.f.s then we must always enter a cycle. 
Otherwise, this would contradict the assumption that there exists a shorter
path to t.f.s when considering paths of arbitrary length than those of 
length at most n-1. The sum of the edge weights along this path is
non-positive, and it can't be zero because then it would have no origin ...
*/
