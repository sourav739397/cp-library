#include <bits/stdc++.h>

using namespace std;

void solve() {
	int n; cin >> n;

	string s; cin >> s;

	int m = n/2;
	int cmid = count(begin(s), end(s), s[m]);
	if ((n&1) && cmid <= n/2) {
		cout << "NO\n";
		return;
	}

	if (n%2 == 0) {
		int m_ = n/2 - 1;
		int cm = count(begin(s), begin(s)+n-1, s[m_]);
		if (cm < n/2) {
			cout << "NO\n";
			return;
		}
		m_++;
		cm = count(begin(s)+1, end(s), s[m_]);
		if (cm < n/2) {
			cout << "NO\n";
			return;
		}
	}

	int l = 0;
	while (l < n && s[l] == s[0] && s[l] != s[m]) {
		l++;
	}
	int r = n-1;
	while (r >= 0 && s[n-1] == s[r] && s[r] != s[m]) {
		r--;
	}

	string t = string(l, s[0]) + string(cmid, s[m]) + string((n-1)-r, s[n-1]);
	cout << (s == t ? "YES" : "NO") << "\n";
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0);

	int Q; cin >> Q;
	while (Q--) { solve(); }
}