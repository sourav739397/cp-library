/**
 * Description: 2D matrix operations.
 * Source: KACTL
 * Verification: https://dmoj.ca/problem/si17c1p5, SPOJ MIFF
 */

#include "../../number-theory (11.1)/Modular Arithmetic/ModInt.h"

using T = mi;
using Mat = vector<vector<T>>; // use array instead if tight TL

Mat makeMat(int r, int c) {
	return Mat(r, vector<T>(c));
}
Mat makeId(int n) {
	Mat m = makeMat(n, n);
	for (int i = 0; i < n; i++) m[i][i] = 1;
	return m;
}

Mat operator+(Mat& a, const Mat& b) {
	assert(sz(a) == sz(b) && sz(a[0]) == sz(b[0]));
	int x = size(a), y = size(a[0]);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < y; j++) {
			a[i][j] += b[i][j];
		}
	}
	return a;
}

Mat operator-(Mat& a, const Mat& b) {
	assert(sz(a) == sz(b) && sz(a[0]) == sz(b[0]));
	int x = size(a), y = size(a[0]);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < y; j++) {
			a[i][j] -= b[i][j];
		}
	}
	return a;
}

Mat operator*(const Mat& a, const Mat& b) {
	int x = size(a), y = size(a[0]), z = size(b[0]); 
	assert(y == sz(b)); Mat c = makeMat(x, z);
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < z; k++) {
				c[i][k] += a[i][j]*b[j][k];
			}
		}
	}
	return c;
}

Mat& operator*=(Mat& a, const Mat& b) { return a = a*b; }
Mat& operator+=(Mat& a, const Mat& b) { return a = a+b; }
Mat& operator-=(Mat& a, const Mat& b) { return a = a-b; }

Mat pow(Mat m, int64_t p) {
	int n = sz(m); assert(n == sz(m[0]) && p >= 0);
	Mat res = makeId(n);
	for (; p; p /= 2, m *= m) if (p&1) res *= m;
	return res;
}