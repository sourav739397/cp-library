// https://toph.co/p/n-th-prime

#include <bits/stdc++.h>

using namespace std;

template<int N> struct Sieve { 
	bitset<N> is_prime; vector<int> primes;
	Sieve() {
		is_prime.set(); is_prime[0] = is_prime[1] = 0;
		for (int i = 4; i < N; i += 2) is_prime[i] = 0;
		for (int i = 3; i*i < N; i += 2) if (is_prime[i])
			for (int j = i*i; j < N; j += i*2) is_prime[j] = 0;
		for (int i = 0; i < N; i++) if (is_prime[i]) primes.push_back(i);
	}
};
Sieve<16<<19> S;

void solve() {
	int n; cin >> n;
	cout << S.primes[n-1] << "\n";
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0);

	solve();
}