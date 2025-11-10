/**
 * Description: A set (not multiset!) with support for finding the $n$'th
   * element, and finding the index of an element. Change \texttt{null\_type} to get a map.
 * Time: O(\log N)
 * Source: KACTL
   * https://codeforces.com/blog/entry/11080
 * Verification: many
 */

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<class T> using Tree = tree<T, null_type, less<T>, 
  rb_tree_tag, tree_order_statistics_node_update>; 
#define ook order_of_key // position of the given element
#define fbo find_by_order // return an iterator

int atMost(Tree<pair<int, int>>& T, int r) { 
	return T.order_of_key({r,MOD}); 
}
int getSum(Tree<pair<int, int>>& T, int l, int r) { 
	return atMost(T,r)-atMost(T,l-1); 
}
