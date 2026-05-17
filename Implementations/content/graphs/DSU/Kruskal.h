/**
 * Description: Computes the weight of a Minimum Spanning Tree (MST)
  * using Kruskal's algorithm. Requires DSU.
 * Time: O(M \log M), where M = number of edges
 * Source: Benq
 */

#include "DSU.h"

template <class T> T Kruskal(int N, vector<array<T, 3>> eg) {
	ranges::sort(eg);
	DSU D(N); T ans = 0;
	for (auto &[w, u, v] : eg) if (D.unite(u, v)) ans += w;
	return ans;
}