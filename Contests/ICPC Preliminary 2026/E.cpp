/**
 * Pigeonhole Principle ->
 * f(x, y) = x^3y - xy^3 = xy(x+y)(x-y)
 * if (m/2) + 1 elements are considered, then 
 *    i. x == 0 (mod m) || y == 0 (mod m)
 *   ii. x+y == 0 (mod m)
 *  iii. x-y == 0 (mod m)
 */

#include <bits/stdc++.h>

using namespace std;

bool f(int x, int y, int m) {
	x %= m, y %= m;
	return (x * y * (x+y) * (x-y+m)) % m == 0;
}

void solve() {
	int n, q; cin >> n >> q;

	vector<int> a(n);
	for(auto& x: a) cin >> x;

	auto qq = [&](int l, int r, int m){
		for (int i = l; i <= r; i++) {
			for (int j = i+1; j <= r; j++) {
				if (f(a[i], a[j], m)) {
					cout << i+1 << " " << j+1 << "\n";
					return;
				}
			}
		}
		cout << "-1\n";
	};

	while (q--) {
		int l, r, m; cin >> l >> r >> m;
		l--, r--; r = min(r, l+m/2+1);
		qq(l, r, m);
	}
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0);

	int Q; cin >> Q;
	while (Q--) { solve(); }
}