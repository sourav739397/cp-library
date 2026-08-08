/**
 * Description: Heavy-Light Decomposition, add val to verts 
 	* and query sum in path/subtree.
 * Time: any tree path is split into $O(\log N)$ parts
 * Source: http://codeforces.com/blog/entry/22072, https://codeforces.com/blog/entry/53170
 * Verification: *
 */

template<class T, bool VALS_IN_EDGES> struct HLD {
	int N, ti = 0;
	SegmentTree<T> seg;
	vector<vector<int>> adj;
	vector<int> par, depth, sz, root, pos, rpos;
	HLD(int _N) : N(_N), seg(N), adj(N), par(N, -1) {
		depth = sz = root = pos = vector<int>(N);
	}
	void ae(int u, int v) {
		adj[u].push_back(v); adj[v].push_back(u);
	}
	void gen(int R = 0) { root[R] = R; dfsSIZE(R); dfsHLD(R); }
	void dfsSIZE(int u) {
		sz[u] = 1;
		for (auto& v: adj[u]) {
			par[v] = u; depth[v] = depth[u]+1;
			adj[v].erase(find(begin(adj[v]), end(adj[v]), u));
			dfsSIZE(v); sz[u] += sz[v];
			if (sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
		}
	}
	void dfsHLD(int u) {
		pos[u] = ti++; rpos.push_back(u);
		for (auto& v: adj[u]) {
			root[v] = (v == adj[u][0] ? root[u] : v);
			dfsHLD(v);
		}
	}
	int lca(int u, int v) {
		for (; root[u] != root[v]; v = par[root[v]]) {
			if (depth[root[u]] > depth[root[v]]) swap(u, v);
		}
		return depth[u] < depth[v] ? u : v;
	}
	int dist(int u, int v) {
		return depth[u] + depth[v] - 2*depth[lca(u, v)];
	}
	template <class F> void processPath(int u, int v, F op) {
		for (; root[u] != root[v]; v = par[root[v]]) {
			if (depth[root[u]] > depth[root[v]]) swap(u, v);
			op(pos[root[v]], pos[v]);
		}
		if (depth[u] > depth[v]) swap(u, v);
		op(pos[u]+VALS_IN_EDGES, pos[v]);
	}
	void modifyNode(int u, T val) {
		seg.update(pos[u], val);
	}
	void modifyPath(int u, int v, T val) {
		processPath(u, v, [&](int l, int r) {
			seg.update(l, r, val);
		});
	}
	void modifySubtree(int u, T val) {
		seg.update(pos[u]+VALS_IN_EDGES, pos[u]+sz[u]-1, val);
	}
	T queryPath(int u, int v) {
		T res = 0;
		processPath(u, v, [&](int l, int r) { 
			res = max(res, seg.query(l, r));
		});
		return res;
	}
};