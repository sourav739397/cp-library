#include <bits/stdc++.h>

using namespace std;

#define int int64_t

pair<double, double> f(int x, int y, int x_, int y_, int a, int b) {
	if (a == 1) {
		double ucx = b*x + a*y - y_;
		double ucy = x_ - a*x + b*y;
		return {ucx/b, ucy/b};
	}
	double ucy = (1ll-a)*y_ - (1ll-a)*(b*x + a*y) + b*x_ - a*b*x + b*b*y;
	double dcy = (1ll-a) * (1ll-a) + b*b;
	double cy = ucy / dcy;

	double ucx = x_ - a*x + b*y - b*cy;
	double cx = ucx / (1ll-a);
	return {cx, cy};
}

void solve() {
	int n, a, b; cin >> n >> a >> b;

	vector<int> x(n), y(n), w(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i];
	}

	for (int i = 0; i < n; i++) {
		cin >> y[i];
	}

	for (int i = 0; i < n; i++) {
		cin >> w[i];
	}

	map<pair<double, double>, int64_t> cnt;
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