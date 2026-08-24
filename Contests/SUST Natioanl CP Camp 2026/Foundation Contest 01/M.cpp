// https://toph.co/p/byangs-day-out

#include <bits/stdc++.h>

using namespace std;

/**
 * in worst case, wall height is highest value
 */
void solve() {
	vector<int> a(3);
	for(auto& x: a) cin >> x;
	ranges::sort(a);

	cout << (a[0]+a[1] >= a[2] ? "Yes" : "No") << "\n";
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0);

	int Q; cin >> Q;
	while (Q--) { solve(); }
}