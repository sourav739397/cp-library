// Problem: https://lightoj.com/problem/rooks

#include <bits/stdc++.h>

using namespace std;

/**
 * maximum n rooks
 * after placeing ith valid rook in (r, c), can't place 
 * other rooks in r'th row or c'th col. so, for next rook
 * there are (n-i+1) * (n-i+1) pos. this way k rooks permute in k! ways.
 */
void solve() {
	int n, k; cin >> n >> k;

	if (k > n) {
		cout << 0 << "\n";
		return;
	}

	__int128_t ans = 1;
	for (int i = 1; i <= k; i++) {
		ans *= (n-i+1);
		ans *= (n-i+1);
		ans /= i;
	}
	cout << (int64_t)ans << "\n";
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0);

	int Q, cs = 0; cin >> Q;
	while (Q--) {
		cout << "Case " << ++cs << ": ";
		solve(); 
	}
}