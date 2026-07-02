/**
 * Description: BFS on the complement graph without explicitly constructing it.
 * Source: jiangly
 * Verification: https://judge.yosupo.jp/problem/connected_components_of_complement_graph
*/

struct ComplementBFS {
	int N;
	set<int> rem;
	vector<set<int>> iadj;
	ComplementBFS(int _N) {
		N = _N;
		iadj.resize(N);
		for (int i = 0; i < N; i++) {
			rem.insert(i);
		}
	}
	void ae(int u, int v) {
		iadj[u].insert(v);
		iadj[v].insert(u);
	}
	void gen(int st) {
		rem.erase(st);
		queue<int> todo; todo.push(st);
		while (todo.size()) {
			int u = todo.front(); todo.pop();
			auto it = rem.begin();
			while (it != rem.end()) {
				int v = *it; auto nxt = next(it);
				if (!iadj[u].contains(v)) {
					todo.push(v);
					rem.erase(it);
				}
				it = nxt;
			}
		}
	}
};