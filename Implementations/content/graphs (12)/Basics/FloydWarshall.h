/**
 * Description: All-Pairs Shortest Path
 * Source: KACTL
 * Verification:
 * https://open.kattis.com/problems/allpairspath
 * https://cses.fi/problemset/task/1672/
 */

void floydWarshall(vector<vector<int64_t>>& dist) {
  int N = size(dist);
  for (int i = 0; i < N; i++) dist[i][i] = min<int64_t>(dist[i][i], 0);
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (dist[i][k] != INT64_MAX && dist[k][j] != INT64_MAX) {
          dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
        }
      }
    }
  }
  for (int k = 0; k < N; k++) {
    if (dist[k][k] < 0) {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          if (dist[i][k] != INT64_MAX && dist[k][j] != INT64_MAX) {
            dist[i][j] = INT64_MIN;
          }
        }
      }
    }
  }
}