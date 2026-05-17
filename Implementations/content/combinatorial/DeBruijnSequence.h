/**
 * Description: Given alphabet $[0,k)$ constructs a cyclic string 
 	* of length $k^n$ that contains every length $n$ string as substr. 
 * Source: https://en.wikipedia.org/wiki/De_Bruijn_sequence
 * Verification: https://cses.fi/problemset/task/1692/
 */ 

vector<int> deBruijnSequence(int k, int n) {
  if (k == 1) return {0};
  vector<int> seq, aux(n+1);
  auto gen = [&](this auto&& self, int t, int p)->void {
    if (t > n) {
      if (n % p == 0) for (int i = 1; i <= p; i++) seq.push_back(aux[i]);
    }
    else {
      aux[t] = aux[t-p]; self(t+1, p);
      while (++aux[t] < k) self(t+1, t);
    }
  };
  gen(1, 1); return seq;
}

void solve() {
  
}

int32_t main() {
  cin.tie(0)->sync_with_stdio(0);

  solve();
}