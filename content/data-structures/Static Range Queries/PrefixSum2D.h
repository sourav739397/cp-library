/**
 * Description: calculates rectangle sums in constant time
 * Source: KACTL
 * Verification: https://cses.fi/problemset/task/1652/
*/

template<typename T> struct PrefixSum2D {
  vector<vector<T>> sum;
  PrefixSum2D(const vector<vector<T>> &v) {
    int n = v.size(), m = v[0].size();
    sum.assign(n+1, vector<T>(m+1, T{}));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        sum[i+1][j+1] = v[i][j] 
        - sum[i][j] + sum[i+1][j] + sum[i][j+1];
      }
    }
  }
  T query(int x1, int y1, int x2, int y2) {
    return sum[x2][y2] + sum[x1-1][y1-1] 
    - sum[x1-1][y2] - sum[x2][y1-1];
  }
};
