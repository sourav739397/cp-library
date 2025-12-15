/**
 * Description: Checks if an undirected graph is bipartite.
  * Colors nodes with 1/2. If not bipartite, returns false.
 * Time: O(N + M)
 * Source: own
 * Verification: https://cses.fi/problemset/task/1668/
 */

struct Bipartite {
  int SZ;
  vector<int> color;
  vector<vector<int>> adj;
  Bipartite(int _SZ) {
    SZ = _SZ;
    adj.resize(SZ);
    color.resize(SZ);
  }
  void ae(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  bool check() {
    queue<int> todo;
    for (int src = 0; src < SZ; src++) {
      if (color[src]) continue;
      color[src] = 1; todo.push(src);
      while (!todo.empty()) {
        int u = todo.front(); todo.pop();
        for (auto& v: adj[u]) {
          if (color[v] == color[u]) return false;
          if (!color[v]) color[v] = 3-color[u], todo.push(v);
        }
      }
    }
    return true;
  }
};