/**
 * Description: Polynomial hash for substrings with two bases.
 * Source: Benq
 * Verification: https://cses.fi/problemset/task/1753/
 */

using H = array<int, 2>;
H makeH(char c) { return {c, c}; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> UID(0.1*MOD, 0.9*MOD);
const H base = {UID(rng), UID(rng)};
H operator+(H l, H r) {
  for (int i = 0; i < 2; i++) {
    if ((l[i] += r[i]) >= MOD) l[i] -= MOD;
  }
  return l;
}
H operator-(H l, H r) {
  for (int i = 0; i < 2; i++) {
    if ((l[i] -= r[i]) < 0) l[i] += MOD;
  }
  return l;
}
H operator*(H l, H r) {
  for (int i = 0; i < 2; i++) {
    l[i] = (1LL*l[i]*r[i]) % MOD;
  }
  return l;
}
vector<H> pows{{1, 1}};
struct HashRange {
  string S; vector<H> sum{{}};
  void add(char c) {
    S += c;
    sum.push_back(base*sum.back()+makeH(c));
  }
  void add(string s) {
    for (auto &c : s) add(c);
  }
  void extend(int len) {
    while ((int)pows.size() <= len) {
      pows.push_back(base * pows.back());
    }
  }
  H hash(int l, int r) {
    int len = r+1-l; extend(len);
    return sum[r+1] - pows[len] * sum[l];
  }
  uint64_t hash64(int l, int r) {
    H p = hash(l, r);
    return (uint64_t) p[0]<<32|p[1];
  }
  /**int lcp(HashRange& b) { return first_true([&](int x) {
    return sum[x] != b.sum[x]; },0,min(sz(S),sz(b.S)))-1; }*/
};
