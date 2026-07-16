
#include "SegmentTree.h"
void LIS() {
	SegmentTree<int> DP(MaxVal+1); // seg store max
	for (int i = 0; i < n; i++) {
		DP.update(a[i], DP.query(0, a[i]-1) + 1);
	}
	cout << DP.seg[1] << "\n";
}