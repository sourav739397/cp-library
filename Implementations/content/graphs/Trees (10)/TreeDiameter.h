/**
 * Description: Calculates longest path in tree. The vertex furthest
 	* from 0 must be an endpoint of the diameter.
 * Source: Benq
 * Verification: 
   * http://www.spoj.com/problems/PT07Z/
   * https://codeforces.com/contest/1182/problem/D
 */

struct TreeDiameter {
  int N, diaLen;  
  vector<int> dist, dia;
  vector<vector<int>> adj;
  TreeDiameter(int _N) {
    N = _N; dia = {0, 0};
    adj.resize(N);
    dist.resize(N);
  }
  void ae(int u, int v) { 
    adj[u].push_back(v);
    adj[v].push_back(u); 
  }
  void genDist(int R) { dist[R] = 0; dfs(R); }
  void gen() {
    genDist(0);
    for (int i = 0; i < N; ++i) {
      if (dist[i] > dist[dia[0]]) dia[0] = i;
    }
    genDist(dia[0]);
    for (int i = 0; i < N; ++i) {
      if (dist[i] > dist[dia[1]]) dia[1] = i;
    }
    diaLen = dist[dia[1]];
    /// center vertex of dia[0] -> dia[1]
    // int cen = dia[1]; 
    // for (int i = 0; i < diaLen/2; ++i) cen = par[cen];
    // center = {cen}; 
    // if (diaLen&1) center.push_back(par[cen]);
  }
  void dfs(int u, int p = -1) {
    for (auto& v: adj[u]) {
      if (v == p) continue;
      dist[v] = dist[u]+1; dfs(v, u); 
    }
  }
};
