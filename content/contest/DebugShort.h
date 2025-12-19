template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
} // pair
template <typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream &operator<<(ostream &os, const C &v) {
  os << '{'; 
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << '}';
} // ds
void dbg_out() { cerr << "|\n"; }
template<typename H, typename... T> void dbg_out(H h, T... t) { 
  cerr << " | "<< h; dbg_out(t...); 
} // basic
#define dbg(...) cerr << __LINE__<< ":[" << #__VA_ARGS__ << "] =", dbg_out(__VA_ARGS__)
