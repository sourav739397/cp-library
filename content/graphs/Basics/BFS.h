/**
 * Description: Performs a standard BFS on an undirected graph.
 * Time: O(N + M)
 * Source: own
 * Verification: https://cses.fi/problemset/task/1667
 */

struct BFS {
  int SZ;
  vector<bool> vis;
  vector<vector<int>> adj;
  BFS(int _SZ) {
    SZ = _SZ;
    adj.resize(SZ);
    vis.resize(SZ);
  }
  void ae(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void bfs(int src) {
    vis[src] = 1;
    queue<int> todo; todo.push(src); 
    while (!todo.empty()) {
      auto u = todo.front(); todo.pop();
      for (auto& v: adj[u]) {
        if (vis[v]) continue;
        vis[v] = 1; 
        todo.push(v);
      }
    }
  }
};