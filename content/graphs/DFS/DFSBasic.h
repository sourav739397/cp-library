/**
 * Description: Basic DFS implementation for undirected graphs
 * Time: O(N+M) 
 * Source: Own
*/

struct DFS {
  int N;
  vector<bool> visited;
  vector<vector<int>> adj;
  DFS(int _N) {
    N = _N;
    adj.resize(N);
    visited.resize(N);
  }
  void ae(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void dfs(int u) {
    visited[u] = true;
    for (auto& v: adj[u]) {
      if (visited[v]) continue;
      dfs(v);
    }
  }
};