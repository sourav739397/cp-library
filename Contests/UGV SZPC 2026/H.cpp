// Corridors of UGV, Barishal

#include <bits/stdc++.h>

using namespace std;

void solve() {
	int n, m; cin >> n >> m;

	vector<bool> ok(n);
	ok[0] = 1;

	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--, v--;
		if (u > v) swap(u, v);
		if (u+1 == v) ok[v] = 1;
	}

	cout << (vector(n, true) == ok ? "YES" : "NO") << "\n"; 
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0);

	int Q; cin >> Q;
	while (Q--) { solve(); }
}