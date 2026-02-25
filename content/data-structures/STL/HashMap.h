/**
 * Description: Hash map with similar API as unordered\_map.
 * Initial capacity must be a power of 2 if provided.
 * Source: KACTL
 * Memory: \tilde 1.5x unordered map
 * Time: \tilde 3x faster than unordered map
 * Usage: gp_hash_table<int, int, chash> h({},{},{},{},{1<<16});
 */

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct chash {
  const uint64_t C = 4e18*acos(0)+71;
  const int R = chrono::steady_clock::now().time_since_epoch().count();
  size_t operator()(uint64_t x) const {
    return __builtin_bswap64((x^R)*C);
  }
};
template <class K, class V> using HT = gp_hash_table<K, V, chash>;
template <class K, class V> V get(HT<K, V> &u, K x) {
  auto it = u.find(x); return it == u.end() ? 0 : it->second;
}