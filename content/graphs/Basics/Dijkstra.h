/**
 * Description: shortest path
 * Time: O(N\log N + M)
 * Source: own
 * Verification: https://cses.fi/problemset/task/1671/
*/

template<class T, bool directed> struct Dijkstra {
  int SZ;
  vector<T> dist;
  vector<vector<pair<int, T>>> adj;
  Dijkstra(int _SZ) {
    SZ = _SZ;
    adj.resize(SZ);
  }
  void ae(int u, int v, T w) {
    adj[u].push_back({v, w});
    if (!directed) adj[v].push_back({u, w});
  }
  void gen(int st) {
    dist.assign(SZ, numeric_limits<T>::max());
    priority_queue<pair<T, int>> PQ;
    auto relax = [&](int v, T d) {
      if (dist[v] <= d) return;
      dist[v] = d; 
      PQ.push({-dist[v], v});
    }; relax(st, 0);
    while (!PQ.empty()) {
      auto [d, u] = PQ.top(); PQ.pop(); d = -d;
      if (dist[u] < d) continue;
      for (auto& [v, w]: adj[u]) relax(v, w+d);
    }
  }
};
