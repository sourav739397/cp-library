/**
 * Description: Tests primality up to $SZ$. Runs faster if only
 	* odd indices are stored.
 * Time: O(SZ\log\log SZ) or O(SZ)
 * Source: KACTL 
 * Verification: https://open.kattis.com/problems/primesieve
 */

template<int SZ> struct Sieve { 
	bitset<SZ> is_prime; vector<int> primes;
	Sieve() {
		is_prime.set(); is_prime[0] = is_prime[1] = 0;
		for (int i = 4; i < SZ; i += 2) is_prime[i] = 0;
		for (int i = 3; i*i < SZ; i += 2) if (is_prime[i])
			for (int j = i*i; j < SZ; j += i*2) is_prime[j] = 0;
		for (int i = 0; i < SZ; i++) if (is_prime[i]) primes.push_back(i);
	}
	// array<int, SZ> spf{} // smallest prime that divides
	// Sieve() { // above is faster
	// 	for (int i = 2; i < SZ; i++) { 
	// 		if (spf[i] == 0) spf[i] = i, primes.push_back(i); 
	// 		for (int p: primes) {
	// 			if (p > spf[i] || i*p >= SZ) break;
	// 			spf[i*p] = p;
	// 		}
	// 	}
	// }
};