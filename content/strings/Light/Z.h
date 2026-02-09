/**
 * Description: \texttt{f[i]} is the max \texttt{len} such that 
 	* \texttt{s.substr(0,len) == s.substr(i,len)}
 * Time: O(N)
 * Source: http://codeforces.com/blog/entry/3107
 * Usage: getPrefix("abcab","uwetrabcerabcab"));
 * Verification: https://codeforces.com/problemset/problem/126/B
 */

vector<int> Zfunction(string s){
  int N = s.size(), L = 1, R = 0; s += '#';
  vector<int> z(N); z[0] = N;
  for (int i = 1; i < N; i++) {
    if (i <= R) z[i] = min(R-i+1, z[i-L]);
    while (s[i+z[i]] == s[z[i]]) ++z[i];
    if (i+z[i]-1 > R) L = i, R = i+z[i]-1;
  }
  return z;
} 
vector<int> getPrefix(string a, string b) { // find prefixes of a in b
	vector<int> t = Zfunction(a+b); 
  t = vector<int>(size(a)+begin(t), end(t)); 
  for (auto& x: t) x = min(x, (int)size(a));
	return t;
}
