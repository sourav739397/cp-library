/**
 * Description: length of largest palindrome centered at each character of string
 * Source: http://codeforces.com/blog/entry/12143
 * Time: O(N)
 	* and between every consecutive pair
 * Verification: http://www.spoj.com/problems/MSUBSTR/
 */

#include "bits/stdc++.h"
using namespace std;

vector<int> Manacher(string _S) {
	string S = "@"; 
  for (auto c: _S) S += c, S += "#";
	S.back() = '&';

	vector<int> ans(size(S)-1); 
	for (int i = 1, lo = 0, hi = 0; i < size(S)-1; i++) {
		if (i != 1) ans[i] = min(hi-i, ans[hi-i+lo]);
		while (S[i-ans[i]-1] == S[i+ans[i]+1]) ++ans[i];
		if (i+ans[i] > hi) lo = i-ans[i], hi = i+ans[i];
	}
	ans.erase(begin(ans));
	for (int i = 0; i < size(ans); i++) {
    if (i%2 == ans[i]%2) ++ans[i]; 
  }
	return ans;
} 
/// Usage: ps(manacher("abacaba"))
