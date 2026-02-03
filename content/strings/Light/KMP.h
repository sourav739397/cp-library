/**
 * Description: \texttt{f[i]} is length of the longest proper suffix 
 	* of the $i$-th prefix of $s$ that is a prefix of $s$
 * Source: KACTL
 * Time: O(N)
 * Verification: https://cses.fi/problemset/task/1753/
 */

vector<int> KMP(string s) {
  int N = s.size();
  vector<int> f(N + 1); f[0] = -1;
  for (int i = 1; i <= N; i++) {
    for (f[i] = f[i-1]; f[i] != -1 && s[f[i]] != s[i-1];) {
      f[i] = f[f[i]];
    }
    ++f[i];
  }
  return f;
}
vector<int> getOc(string a, string b){ // find occurrences of a in b
  vector<int> f = KMP(a + "@" + b), res;
  for (int i = a.size(); i <= b.size(); i++) {
    if (f[i+a.size()+1] == a.size()) {
      res.push_back(i - a.size());
    }
  }
  return res;
}
