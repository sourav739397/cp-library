#define uid(l, r) uniform_int_distribution<int>(l, r)(rng)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());