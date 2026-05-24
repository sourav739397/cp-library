/**
 * Description: Biconnected components of edges. Removing any vertex in BCC
 	* doesn't disconnect it. To get block-cut tree, create a bipartite graph
 	* with the original vertices on the left and a vertex for each BCC on the right. 
 	* Draw edge $u\leftrightarrow v$ if $u$ is contained within the BCC for $v$.
 	* Self-loops are not included in any BCC while BCCS of size 1 represent
 	* bridges.
 * Time: O(N+M)
 * Source: GeeksForGeeks (corrected)
 * Verification: 
 	* USACO December 2017, Push a Box -> https://pastebin.com/yUWuzTH8
 	* https://cses.fi/problemset/task/1705/
 */

#include "bits/stdc++.h"
using namespace std;

struct BCC {
	vector<pair<int, int>> ed; 
	vector<vector<pair<int, int>>> adj;
	vector<vector<int>> edgeSets, vertSets; // edges for each bcc
	int N, ti = 0; 
	vector<int> disc, stk; 
	BCC(int _N) { 
		N = _N; 
		disc.resize(N), adj.resize(N); 
	}
	void ae(int u, int v) { 
		adj[u].emplace_back(v, size(ed));
		adj[v].emplace_back(u, size(ed));
		ed.emplace_back(u, v); 
	}
	int dfs(int u, int p = -1) { // return lowest disc
		int low = disc[u] = ++ti;
		for (auto e : adj[u]) if (e.s != p) {
			if (!disc[e.f]) {
				stk.pb(e.s); // disc[x] < LOW -> bridge
				int LOW = dfs(e.f,e.s); ckmin(low,LOW); 
				if (disc[x] <= LOW) { // get edges in bcc
					edgeSets.eb(); vi& tmp = edgeSets.bk; // new bcc
					for (int y = -1; y != e.s; )
						tmp.pb(y = stk.bk), stk.pop_back();
				}
			} else if (disc[e.f] < disc[x]) // back-edge
				ckmin(low,disc[e.f]), stk.pb(e.s);
		}
		return low;
	}
	void gen() { 
		F0R(i,N) if (!disc[i]) dfs(i);  
		vb in(N);
		each(c,edgeSets) { // edges contained within each BCC
			vertSets.eb(); // so you can easily create block cut tree
			auto ad = [&](int x) { 
				if (!in[x]) in[x] = 1, vertSets.bk.pb(x); };
			each(e,c) ad(ed[e].f), ad(ed[e].s);
			each(e,c) in[ed[e].f] = in[ed[e].s] = 0;
		}
	}
};
