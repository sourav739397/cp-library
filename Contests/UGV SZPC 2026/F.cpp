// Three Sides of Triangle

#include <bits/stdc++.h>

using namespace std;

void solve() {
	int n; cin >> n;

	vector<pair<int, int>> vp(n);
	for (int i = 0; i < 3; i++) {
		int x; cin >> x;
		vp[i] = {x, i};
	}
	ranges::sort(vp);

	vector<int> a(n);
	for(auto& x: a) cin >> x;
	ranges::sort(a, greater<>());
	
	vector<vector<int>> ans(3);
	int st = 0;
	for (auto& [sz, id]: vp) {
		for (int i = st; i < st+sz; i++) {
			ans[id].push_back(a[i]);
		}
		st += sz;
	}

	vector<int64_t> v(3);
	for (int i = 0; i < 3; i++) {
		v[i] = accumulate(begin(ans[i]), end(ans[i]), 0ll);
	}
	ranges::sort(v);

	if (v[0] + v[1] <= v[2]) {
		cout << "NO\n";
		return;
	}

	cout << "YES\n";
	for (auto& x: ans) {
		for (auto& y: x) {
			cout << y << " ";
		}
		cout << "\n";
	}
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0);

	int Q; cin >> Q;
	while (Q--) { solve(); }
}