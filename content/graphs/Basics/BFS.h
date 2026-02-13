/**
 * Description: Performs a standard BFS on an undirected graph.
 * Time: O(N + M)
 * Source: own
 * Verification: https://cses.fi/problemset/task/1667
 */

struct BFS {
  int N;
  vector<vector<int>> adj;
  BFS(int _N) {
    N = _N; adj.resize(N);
  }
  void ae(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void gen(int src) {
    dist[src] = 0;
    queue<int> todo; todo.push(src); 
    while (!todo.empty()) {
      auto u = todo.front(); todo.pop();
      for (auto& v: adj[u]) if (dist[v] == -1) {
        dist[v] = dist[u]+1; todo.push(v);
      }
    }
  }
};