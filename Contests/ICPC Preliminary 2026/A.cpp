#include <bits/stdc++.h>

using namespace std;

#define int int64_t

pair<int64_t, int64_t> f(int x, int y, int x_, int y_, int a, int b) {
	// x' = ax - by + dx
	// y' = bx + ay + dy
	return {1ll*x_-1ll*x*a+1ll*y*b, 1ll*y_-1ll*x*b-1ll*y*a};
}

void solve() {
	int n, a, b; cin >> n >> a >> b;

	vector<int> x(n), y(n), w(n);
	for (int i = 0; i < n; i++) cin >> x[i];
	for (int i = 0; i < n; i++) cin >> y[i];
	for (int i = 0; i < n; i++) cin >> w[i];

	map<pair<int64_t, int64_t>, int64_t> cnt;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			auto val = f(x[i], y[i], x[j], y[j], a, b);
			cnt[val] += w[i];
		}
	}

	int64_t ans = 0;
	for (auto& [_, v]: cnt) {
		ans = max(ans, v);
	}

	cout << ans << "\n";
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0);

	int Q; cin >> Q;
	while (Q--) { solve(); }
}