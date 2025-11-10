/**
 * Description: stack
 * Source: https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
 * Verification: VT HSPC 2019 D
 */

struct DirectedCycle {
  int SZ;
  vector<bool> inStk, vis;
  vector<int> stk, cyc;
  vector<vector<int>> adj;
  DirectedCycle(int _SZ) {
    SZ = _SZ;
    adj.resize(SZ);
    inStk.resize(SZ), vis.resize(SZ);
  }
  void ae(int u, int v) { adj[u].push_back(v); }
  vector<int> gen() {
    for (int u = 0; u < SZ; u++) {
      if (!vis[u] && empty(cyc)) dfs(u);
    }
    return cyc;
  }
  void dfs(int u) {
    stk.push_back(u);
    inStk[u] = vis[u] = 1;
    for (auto& v: adj[u]) {
      if (inStk[v]) cyc = {ranges::find(stk, v), end(stk)};
      else if (!vis[v]) dfs(v);
      if (size(cyc)) return;
    }
    stk.pop_back();
    inStk[u] = 0;
  }
};
