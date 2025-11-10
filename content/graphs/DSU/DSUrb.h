/**
 * Description: Disjoint Set Union with Rollback
 * Source: see DSU
 * Verification: *
 */

struct DSUrb {
	vector<int> e; 
	vector<array<int,4>> mod;
  DSUrb(int n) { e = vector<int>(n,-1); }
	int get(int x) { return e[x] < 0 ? x : get(e[x]); } 
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) { // union-by-rank
		x = get(x), y = get(y); 
		if (x == y) { 
      mod.push_back({-1,-1,-1,-1}); 
      return 0; 
    }
		if (e[x] > e[y]) swap(x,y);
		mod.push_back({x,y,e[x],e[y]});
		e[x] += e[y]; e[y] = x; return 1;
	}
	void rollback() {
		auto a = mod.back(); mod.pop_back();
		if (a[0] != -1) {
      e[a[0]] = a[2];
      e[a[1]] = a[3];
    }
	}
};
