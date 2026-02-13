/**
 * Description: sorts vertices such that if there exists an edge x->y, then x goes before y
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/quantumsuperposition
 */

struct TopoSort {
  int N;
  vector<int> in, res;
  vector<vector<int>> adj;
  TopoSort(int _N) {
    N = _N; in.resize(N); adj.resize(N);
  }
  void ae(int u, int v) { 
    adj[u].push_back(v), ++in[v]; 
  }
  bool sort() {
    queue<int> todo;
    for (int u = 0; u < N; ++u) if (!in[u]) todo.push(u);
    while (!todo.empty()) {
      int u = todo.front(); todo.pop(); res.push_back(u);
      for (auto &v: adj[u]) if (!(--in[v])) todo.push(v);
    }
    return (int)res.size() == N;
  }
};
