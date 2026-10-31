#include <bits/stdc++.h>

using namespace std;

void solve() {
	int n; cin >> n;
	string s; cin >> s;

	for (int len = 1; len <= n; len+=2) {
		map<char, int> f;
		for (int i = 0; i <len; i++) {
			f[s[i]]++;
		}
		int m = len/2;
		if (f[s[m]] <= len/2) {
			cout << "NO\n";
			return;
		}
		m++;
 		for (int r = len, l = 0 ; r < n; r++, m++) {
			f[s[r]]++, f[s[l]]--; l++;
			if (f[s[m]] <= len/2) {
				cout << "NO\n";
				return;
			}
		}
	}
	cout << "YES\n";
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0);

	int Q; cin >> Q;
	while (Q--) { solve(); }
}