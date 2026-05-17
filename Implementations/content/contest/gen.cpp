#include "bits/stdc++.h"
#include "assert.h"
using namespace std;


////////////// DISTRIBUTIONS
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// return int in [L,R] inclusive
int rng_int(int L, int R) { 
  assert(L <= R); 
	return uniform_int_distribution<int>(L, R)(rng); 
}
int64_t rng_int64(int64_t L, int64_t R) { 
  assert(L <= R); 
	return uniform_int_distribution<int64_t>(L, R)(rng);  
}

// return double in [L,R] inclusive
double rng_db(double L, double R) { assert(L <= R);
	return uniform_real_distribution<double>(L, R)(rng); 
}

// http://cplusplus.com/reference/random/geometric_distribution/geometric_distribution/
// flip a coin which is heads with probability p until you flip heads
// mean value of c is 1/p-1
int rng_geo(double p) { 
  assert(0 < p && p <= 1); // p large -> closer to 0
	return geometric_distribution<int>(p)(rng); 
}

////////////// VECTORS + PERMS

// shuffle a vector
template<class T> void randShuffle(vector<T>& v) {
  shuffle(begin(v), end(v), rng);
}

// generate random permutation of [0,N-1]
vector<int> randPermutation(int N) { 
  vector<int> v(N); iota(begin(v), end(v), 0); 
  randShuffle(v); return v; 
}

// random permutation of [0,N-1] with first element 0
vector<int> randPermutationZero(int N) {
  vector<int> v(N-1); iota(begin(v), end(v), 1); 
	randShuffle(v); 
  v.insert(begin(v), 0); return v; 
}

// shuffle permutation of [0,N-1]
vi shufPerm(vi v) {
	int N = sz(v); vi key = randPerm(N);
	vi res(N); F0R(i,N) res[key[i]] = key[v[i]];
	return res;
}

// vector with all entries in [L,R]
vector<int> randVector(int N, int L, int R) {
  vector<int> v(N);
  for (int i = 0; i < N; i++) {
    v[i] = rng_int(L, R);
  }
  return v;
}

// vector with all entries in [L,R], unique
vector<int> rngDistinctVector(int N, int L, int R) {
	set<int> used; vector<int> v;
	while ((int)size(v) < N) {
		int x = rng_int(L, R);
		if (!used.count(x)) {
			used.insert(x);
			v.push_back(x);
		}
	} return v;
}

// generate random prime in [L,R]
int randPrime(int L, int R) {
	while(1) {
		int x = rng_int(L, R);
		bool bad = 0;
		for (int i = 2; i*i <= x; i++) if (x%i == 0) bad = 1;
		if (!bad) return x;
	}
}

////////////// GRAPHS

// relabel edges ed according to perm, shuffle
vpi relabelAndShuffle(vpi ed, vi perm) {
	each(t,ed) {
		t.f = perm[t.f], t.s = perm[t.s];
		if (rng()&1) swap(t.f,t.s);
	}
	shuf(ed); return ed;
}

// shuffle graph with vertices [0,N-1]
vpi shufGraph(int N, vpi ed) { // randomly swap endpoints, rearrange labels
	return relabelAndShuffle(ed,randPerm(N)); }
vpi shufGraphZero(int N, vpi ed) {
	return relabelAndShuffle(ed,randPermZero(N)); }

// shuffle tree given N-1 edges
vpi shufTree(vpi ed) { return shufGraph(sz(ed)+1,ed); }
// randomly swap endpoints, rearrange labels
vpi shufRootedTree(vpi ed) {
	return relabelAndShuffle(ed,randPermZero(sz(ed)+1)); }

void pgraphOne(int N, vpi ed) {
	ps(N,sz(ed));
	each(e,ed) ps(1+e.f,1+e.s);
}

////////////// GENERATING TREES

// for generating tall tree
pi geoEdge(int i, db p) { assert(i > 0); 
	return {i,max(0,i-1-rng_geo(p))}; }

// generate edges of tree with verts [0,N-1]
// smaller back -> taller tree
vpi treeRand(int N, int back) { 
	assert(N >= 1 && back >= 0); vpi ed; 
	FOR(i,1,N) ed.eb(i,i-1-rng_int(0,min(back,i-1)));
	return ed; }

// generate path
vpi path(int N) { return treeRand(N,0); }

// generate tall tree (large diameter)
// the higher the p the taller the tree
vpi treeTall(int N, db p) { assert(N >= 1); 
	vpi ed; FOR(i,1,N) ed.pb(geoEdge(i,p));
	return ed; }

// generate tall tree, then add rand at end
vpi treeTallShort(int N, db p) { 
	assert(N >= 1); int mid = (N+1)/2;
	vpi ed = treeTall(mid,p); 
	FOR(i,mid,N) ed.eb(i,rng_int(0,i-1));
	return ed; }

// lots of stuff connected to either heavy1 or heavy2
vpi treeTallHeavy(int N, db p) { 
	assert(N >= 1); // + bunch of rand
	vpi ed; int heavy1 = 0, heavy2 = N/2;
	FOR(i,1,N) {
		if(i < N/4) ed.eb(i,heavy1);
		else if (i > heavy2 && i < 3*N/4) ed.eb(i,heavy2);
		else ed.pb(geoEdge(i,p));
	}
	return ed;
}

// heavy tall tree + random
// lots of verts connected to heavy1 or heavy2
vpi treeTallHeavyShort(int N, db p) { 
	assert(N >= 1); // + almost-path + rand
	vpi ed; int heavy1 = 0, heavy2 = N/2;
	FOR(i,1,N) {
		if(i < N/4) ed.eb(i,heavy1);
		else if (i <= heavy2) ed.pb(geoEdge(i,p)); // tall -> heavy1
		else if (i > heavy2 && i < 3*N/4) ed.eb(i,heavy2);
		else ed.eb(i,rng_int(0,i-1));
	}
	return ed;
}

int main(int, char* argv[]) {
	int tc; sscanf(argv[1],"%d",&tc); // test case #
  rng.seed(tc);
	// sscanf(argv[2],"%d",&b); // random seed
	// sscanf(argv[3],"%d",&c); // also random seed
	
}