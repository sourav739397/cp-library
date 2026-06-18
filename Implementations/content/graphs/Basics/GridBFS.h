/**
 * Description: BFS through grid with fixed xdir and ydir arrays
 * Verification: https://cses.fi/problemset/task/1193/
 * Source: own
*/

using P = array<int, 2>;
tuple<int, int, char> moves[]{
	{0, 1, 'R'}, {1, 0, 'D'}, {0, -1, 'L'}, {-1, 0, 'U'}
};
struct GridBFS {
	int N, M;
	vector<vector<int>> dist;
	vector<string> grid, dir;
	vector<vector<P>> pre;
	GridBFS(int _N, int _M, vector<string>& _g) {
		N = _N, M = _M, grid = _g;
		dist.resize(N, vector(M, -1));
		dir.resize(N, string(M, '.'));
		pre.resize(N, vector<P>(M, {-1, -1}));
	}
	bool valid(int x, int y) {
		return !(x < 0 || x >= N || y < 0 || y >= M);
	}
	void gen(P& st) {
		queue<P> todo;
		todo.push(st); dist[st[0]][st[1]] = 0;
		while (todo.size()) {
			auto u = todo.front(); todo.pop();
			for (auto& [dx, dy, di]: moves) {
				P v = {u[0]+dx, u[1]+dy};
				if (!valid(v[0], v[1]) || dist[v[0]][v[1]] != -1) continue;
				todo.push(v);
				dist[v[0]][v[1]] = dist[u[0]][u[1]] + 1;
				pre[v[0]][v[1]] = u, dir[v[0]][v[1]] = di;
			}
		}
	}
	string getPath(P& st, P en) {
		if (dist[en[0]][en[1]] == -1) return "";
		string res;
		while (en != st) {
			auto& [x, y] = en;
			res += dir[x][y]; en = pre[x][y];
		}
		ranges::reverse(res);
		return res;
	}
};
