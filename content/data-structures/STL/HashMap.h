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
	const int RANDOM = chrono::steady_clock::now().time_since_epoch().count();
	int64_t operator()(int64_t x) const { return __builtin_bswap64((x^RANDOM)*C); }
};