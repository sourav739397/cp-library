/**
 * Description: Tests primality up to $N$. Runs faster if only
 	* odd indices are stored.
 * Time: O(N\log\log N) or O(N)
 * Source: KACTL 
 * Verification: https://open.kattis.com/problems/primesieve
 */

template<int N> struct Sieve { 
	bitset<N> is_prime; vector<int> primes;
	Sieve() {
		is_prime.set(); is_prime[0] = is_prime[1] = 0;
		for (int i = 4; i < N; i += 2) is_prime[i] = 0;
		for (int i = 3; i*i < N; i += 2) if (is_prime[i])
			for (int j = i*i; j < N; j += i*2) is_prime[j] = 0;
		for (int i = 0; i < N; i++) if (is_prime[i]) primes.push_back(i);
	}
	// array<int, N> spf{} // smallest prime that divides
	// Sieve() { // above is faster
	// 	for (int i = 2; i < N; i++) { 
	// 		if (spf[i] == 0) spf[i] = i, primes.push_back(i); 
	// 		for (int p: primes) {
	// 			if (p > spf[i] || i*p >= N) break;
	// 			spf[i*p] = p;
	// 		}
	// 	}
	// }
};