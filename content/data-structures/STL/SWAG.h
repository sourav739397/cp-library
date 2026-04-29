/**
 * Description: SWAG (Sliding Window Aggregation) using two stacks.
  * Supports queue operations with O(1) amortized aggregate queries.
  * Works for any associative operation (OR, AND, XOR, GCD, MIN, MAX, SUM, etc).
 * Source: https://codeforces.com/blog/entry/143351
 * Time: push O(1), pop O(1) amortized, query O(1)
 * Memory: O(n)
 * Usage:
 *   Queue<int> q;
 *   q.push(x);
 *   q.pop();
 *   q.query(); // aggregate over all elements in queue
 */

template<class T> struct Stack {
  vector<pair<T, T>> stk;
  T cmb(T x) {
    return stk.empty() ? x : min(stk.back().second, x);
  }
  void push(T x) { stk.push_back({x, cmb(x)}); } 
  void pop() { stk.pop_back(); }
  T agg() const { return stk.back().second; }
};
 
template<class T> struct Queue {
  Stack<T> in, out;
  T cmb(T a, T b) {
    return min(a, b);
  }
  void push(T x) { in.push(x); } 
  void pop() { 
    if (out.stk.empty()) while (!in.stk.empty()) {
      out.push(in.stk.back().first);
      in.pop();
    }
    out.pop();
  }
  T query() {
    if (in.stk.empty()) return out.agg();
    if (out.stk.empty()) return in.agg();
    return cmb(in.agg(), out.agg());
  }
};