/**
 * Description: Calculates least common ancestor in tree with verts 
 	* $0\ldots N-1$ and root $R$ using binary jumping. 
 * Time: O(N\log N) build, O(\log N) query
 * Memory: O(N\log N)
 * Source: Benq, cp-algorithm
 * Verification: https://judge.yosupo.jp/problem/lca
**/

struct LCA {
  int N, LOG;
  vector<int> depth;
  vector<vector<int>> par, adj; 
  LCA(int _N) {  
    N = _N; LOG = 1;
    while ((1<<LOG) < N) ++LOG;
    adj.resize(N); 
    depth.resize(N);
    par.resize(N, vector<int>(LOG));
  }
  void ae(int u, int v) { 
    adj[u].push_back(v);
    adj[v].push_back(u); 
  }
  void gen(int R = 0) { par[R][0] = R; dfs(R); }
  void dfs(int u = 0) {
    for (int j = 1; j < LOG; ++j) {
      par[u][j] = par[par[u][j-1]][j-1];
    }
    for (auto& v: adj[u]) {
      if (v == par[u][0]) continue;
      depth[v] = depth[u]+1; 
      par[v][0] = u;
      dfs(v);
    }
  }
  int jump(int x, int d) {
    for (int j = 0; j < LOG; ++j) {
      if ((d>>j) & 1) x = par[x][j];
    }
    return x; 
  }
  int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    v = jump(v, depth[v]-depth[u]); 
    if (u == v) {return u; }
    for (int j = LOG-1; j >= 0; --j) {
      int U = par[u][j], V = par[v][j];
      if (U != V) u = U, v = V;
    }
    return par[u][0];
  }
  int dist(int u, int v) {
    return depth[u] + depth[v] - 2*depth[lca(u, v)]; 
  }
};