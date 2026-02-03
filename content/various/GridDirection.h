/**
 * Description: Predefined direction for grid-based problems.
  * Includes common movement sets for 2D and 3D grids such as
  * 4-directional, 8-directional, diagonal-only, knight moves, 3D etc.
 * Source: Own
 * Verification: Multiple grid problems (BFS/DFS, CF style)
 */

// Down, Right, Up, Left
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
const char dc[4] = {'D', 'R', 'U', 'L'};

// Down, Down-Right, Right, Up-Right, Up, Up-Left, Left, Down-Left
const int dx8[8] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dy8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

// Diagonals only
const int dxDiag[4] = {1, 1, -1, -1};
const int dyDiag[4] = {1, -1, 1, -1};

// Knight moves
const int dxK[8] = {2, 2, 1, 1, -1, -1, -2, -2};
const int dyK[8] = {1, -1, 2, -2, 2, -2, 1, -1};


// 3D Grid
const int dx[6] = {1, -1, 0, 0, 0, 0};
const int dy[6] = {0, 0, 1, -1, 0, 0};
const int dz[6] = {0, 0, 0, 0, 1, -1};
