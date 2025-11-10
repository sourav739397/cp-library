template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream &operator<<(ostream &os, const C &v) {
  os << '{'; 
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << '}';
}
void dbg_out() { cerr << " |\n"; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { 
  cerr << " | " << H; dbg_out(T...); 
}
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "] =", dbg_out(__VA_ARGS__)
