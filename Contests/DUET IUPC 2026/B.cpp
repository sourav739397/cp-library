// https://codeforces.com/gym/106619/problem/B

#include <bits/stdc++.h>
using namespace std;

const int N = 200'00'02;
int64_t pre[N];

template<int N> struct Sieve {
	bitset<N> is_prime; vector<int> primes;
	int spf[N];
	Sieve() {
		for (int i = 1; i < N; i += 2) spf[i] = i;
		for (int i = 2; i < N; i += 2) spf[i] = 2;
		for (int i = 3; i*i < N; i += 2) if (spf[i] == i)
		for (int j = i*i; j < N; j += i*2) if (spf[j] == j) spf[j] = i;
	}
};
Sieve<N> S;

int divisor2Count(int x) {
	int cnt = 1;
	while (x > 1) {
		int p = S.spf[x];
		int t = 1;
		while (x % p == 0) {
			t += 2;
			x /= p;
		}
		cnt *= t;
	}
	return cnt;
}

void solve() {
	int n; cin >> n;
	cout << pre[n] << "\n";
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0);

	for (int i = 2; i < N; i++) {
		pre[i] = pre[i-1] + divisor2Count(i)/2;
	}

	int Q; cin >> Q;
	while (Q--) { solve(); }
}