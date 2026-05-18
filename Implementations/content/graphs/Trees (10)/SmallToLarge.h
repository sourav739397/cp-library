/**
 * Description: offline subtree queries in $O(N\log^2N)$. 
  * Marge small to large makes $O(logN)$.
 * Source: Wxssim
 * Verification: https://codeforces.com/contest/600/problem/E
 */

struct SmallToLarge {
  int N;
  vector<int64_t> ans, maxOc;
  vector<vector<int>> adj;
  SmallToLarge(int _N) {
    N = _N; 
    adj.resize(N);
    ans.resize(N), maxOc.resize(N);
  }
  void ae(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void cmb(map<int, int>& U, map<int, int>& V, int u) {
    for (auto& [v, c]: V) {
      int cur = U[v] += c;
      if (cur > maxOc[u]) ans[u] = 0, maxOc[u] = cur;
      if (cur == maxOc[u]) ans[u] += v; 
    }
  }
  map<int, int> dfs(int u, int p, vector<int>& a) {
    map<int, int> U{{a[u], 1}};
    ans[u] = a[u], maxOc[u] = 1;
    for (auto& v: adj[u]) if (v != p) {
      auto V = dfs(v, u, a);
      if (U.size() < V.size()) { // main idea 
        swap(U, V);
        ans[u] = ans[v], maxOc[u] = maxOc[v];
      }
      cmb(U, V, u);
    }
    return U;
  }
};
