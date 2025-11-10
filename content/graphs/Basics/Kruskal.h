/**
 * Description: Computes the weight of a Minimum Spanning Tree (MST)
 * using Kruskal's algorithm. Requires DSU.
 * Time: O(M \log M), where M = number of edges
 * Source: own
 * Verification: *
 */

#include "../DSU/DSU.h"

template<class T> T Kruskal(int N, vector<array<T, 3>> eg) {
  ranges::sort(eg);
  T ans = 0; DSU D(N);
  for (auto &[w, u, v] : eg) {
    if (D.unite(u, v)) ans += w;
  }
  return ans;
};