/**
 * Description: Disjoint Set Union with path compression
 	* and union by size. Add edges and test connectivity. 
 	* Use for Kruskal's or Boruvka's minimum spanning tree.
 * Time: O(\alpha(N))
 * Source: CSAcademy, KACTL
 * Verification: https://judge.yosupo.jp/problem/unionfind
*/

struct DSU {
  vector<int> e;
  DSU(int N) { e = vector<int>(N, -1); }
  int get(int u) { return e[u] < 0 ? u : e[u] = get(e[u]); }
  bool sameSet(int u, int v) { return get(u) == get(v); }
  int size(int u) { return -e[get(u)]; }
  bool unite(int u, int v) { // union by size
    u = get(u), v = get(v); if (u == v) return false;
    if (e[u] > e[v]) swap(u, v);
    e[u] += e[v]; e[v] = u; return true;
  }
};
