// Fund Collection

#include <bits/stdc++.h>

using namespace std;

void solve() {
	int n, m; cin >> n >> m;

	vector<vector<int>> adj(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	int ans = 1;
	for (int i = 1; i < n; i++) {
		vector<int> dist(n, -1); dist[i] = 0;
		queue<int> todo; todo.push(i);
		while (todo.size()) {
			int u = todo.front(); todo.pop();
			for (auto& v: adj[u]) if (dist[v] == -1 && v < i) {
				dist[v] = dist[u] + 1;
				todo.push(v);
			}
		}
		if (dist[i-1] == -1) {
			cout << "NO\n";
			return;
		}
		ans += 2*dist[i-1];
	}
	
	vector<int> dist(n, -1); dist[0] = 0;
	queue<int> todo; todo.push(0);
	while (todo.size()) {
		int u = todo.front(); todo.pop();
		for (auto& v: adj[u]) if (dist[v] == -1) {
			dist[v] = dist[u] + 1;
			todo.push(v);
		}
	}
	ans += dist[n-1];

	cout << "YES\n";
	cout << ans << "\n";
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0);

	int Q; cin >> Q;
	while (Q--) { solve(); }
}