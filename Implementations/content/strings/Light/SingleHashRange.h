/**
 * Description: Polynomial hash for substrings with single base.
  	* Use when Memory Limit is tight
 * Source: Own
 * Verification: https://codeforces.com/problemset/problem/7/D
*/

#include "ModIntShort.h"

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> UID(0.1*MOD, 0.9*MOD);

const mint base = UID(rng);
vector<mint> pows(1, 1);
struct HashRange {
	string S; vector<mint> sum{0};
	void add(char c) {
		S += c;
		sum.push_back(base*sum.back()+c);
	}
	void add(string s) {
		for (auto &c : s) add(c);
	}
	void extend(int len) {
		while ((int)pows.size() <= len) {
			pows.push_back(base*pows.back());
		}
	}
	int hash(int l, int r) {
		int len = r+1-l; extend(len);
		return (int)(sum[r+1]-pows[len]*sum[l]);
	}
};