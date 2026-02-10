/**
 * Description: BFS through grid with fixed xdir and ydir arrays
 * Source: Own
 */

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

bool valid(int x, int y) {
  return !(x < 0 || x >= n || y < 0 || y >= m);
}

void bfs(pair<int, int> src) {
  dist[src.first][src.second] = 0;
  queue<pair<int, int>> todo; todo.push(src);
  while (!todo.empty()) {
    auto [uX, uY] = todo.front(); todo.pop();
    for (int i = 0; i < 4; i++) {
      int vX = uX+dx[i], vY = uY+dy[i];
      if (!valid(vX, vY) || dist[vX][vY] != -1) continue;
      dist[vX][vY] = dist[uX][uY]+1;
      todo.push({vX, vY});
    }
  }
}
