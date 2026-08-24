// https://www.codechef.com/problems/ICPC16A

#include <bits/stdc++.h>

using namespace std;

void solve() {
	int x1, y1, x2, y2; 
	cin >> x1 >> y1 >> x2 >> y2;


	if (x1 != x2 && y1 != y2) {
		cout << "sad\n";
		return;
	}
	if (x1 < x2) cout << "right\n";
	if (x1 > x2) cout << "left\n";
	if (y1 < y2) cout << "up\n";
	if (y1 > y2) cout << "down\n";
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0);

	int Q; cin >> Q;
	while (Q--) { solve(); }
}