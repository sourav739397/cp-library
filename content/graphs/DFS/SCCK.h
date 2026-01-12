/**
 * Description: Kosaraju's Algorithm, DFS twice to generate
  * strongly connected components in topological order. $a,b$
  * in same component if both $a\to b$ and $b\to a$ exist.
 * Time: O(N+M)
 * Source: Wikipedia
 * Verification: https://judge.yosupo.jp/problem/scc 
 */

struct SCC {
  int N;
  vector<bool> vis;
  vector<vector<int>> adj, radj;
  vector<int> todo, comp, comps;
  SCC(int _N) {
    N = _N;
    adj.resize(N), radj.resize(N);
    comp.resize(N, -1), vis.resize(N);
  }
  void ae(int u, int v) {
    adj[u].push_back(v);
    radj[v].push_back(u);
  }
  void dfs(int u) {
    vis[u] = true;
    for (auto &v: adj[u]) if (!vis[v]) dfs(v);
    todo.push_back(u);
  }
  void dfs2(int u, int id) {
    comp[u] = id;
    for (auto &v: radj[u]) if (comp[v] == -1) dfs2(v, id);
  }
  void gen() {
    for (int u = 0; u < N; u++) if (!vis[u]) dfs(u);
    ranges::reverse(todo);
    for (auto &u: todo) if (comp[u] == -1) {
      dfs2(u, u);
      comps.push_back(u);
    }
  }
};