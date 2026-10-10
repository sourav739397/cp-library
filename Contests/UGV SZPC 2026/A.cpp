// UGV Sun Car

#include <bits/stdc++.h>

using namespace std;

void solve() {
	int n; cin >> n;
	
	vector<int64_t> DP(n+1);
	int64_t sum = 0;
	for (int i = 1; i <= n; i++) {
		DP[i] = sum-DP[i-1] + 1;
		sum += DP[i];
	}
	
	cout << sum+1 << "\n";
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0);


	int Q; cin >> Q;
	while (Q--) { solve(); }
}