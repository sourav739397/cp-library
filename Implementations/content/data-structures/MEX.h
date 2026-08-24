
template<class T> struct MEXQuery {
	vector<T> v;
	set<T> unseen;
	map<T, int> f;
	MEXQuery(const vector<T>& _v) : v(_v) {
		for (int i = 0; i < v.size(); i++) unseen.insert(i);
		for (auto& x: v) {
			f[x]++;
			unseen.erase(x);
		}
	}
	void update(int p, T val) {
		if (--f[v[p]] == 0) unseen.insert(v[p]);
		f[v[p] = val]++;
		unseen.erase(val);
	}
	T mex() { *unseen.begin(); }
};