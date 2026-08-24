// https://toph.co/p/gcd-plus-lcm

#include <bits/stdc++.h>

using namespace std;

/**
 * let, g = gcd(a, b). so, a = gx, b = gy;
 * lcm = gxy. 
 * g + gxy = gx + gy
 * 1 + xy = x + y
 * (x-1) (y-1) = 0
 * x = 1 or y = 1
 * so, a|b or b|a
 */
void solve() {
	int64_t a, b; cin >> a >> b;
	if (a > b) swap(a, b);

	if (b%a == 0) cout << "true\n";
	else cout << "false\n";
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0);

	int Q; cin >> Q;
	while (Q--) { solve(); }
}