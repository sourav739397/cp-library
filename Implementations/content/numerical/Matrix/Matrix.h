/**
 * Description: 2D matrix operations.
 * Source: KACTL
 * Verification: https://cses.fi/problemset/task/1722/
*/

#include "ModIntShort.h"

template<class T> struct Mat {
	int N, M; vector<vector<T>> v;
	Mat() : Mat(0,0) {}
	Mat(int _N, int _M) : N(_N), M(_M) {
		v.assign(N, vector<T>(M));
	}
	Mat(const vector<vector<T>>& _v) {
		v = _v;
		N = v.size(), M = v[0].size();
	}
	void makeId() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				v[i][j] = (i == j);
			}
		}
	}
	Mat& operator+=(const Mat& o) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				v[i][j] += o.v[i][j];
			}
		}
		return *this; }
	Mat& operator-=(const Mat& o) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				v[i][j] -= o.v[i][j];
			}
		}
		return *this; }
	Mat& operator*=(const Mat& o) {
		Mat ans(N, o.M);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				for (int k = 0; k < o.M; k++) {
					ans.v[i][k] += v[i][j]*o.v[j][k];
				}
			}
		}
		return *this = move(ans); }
	friend Mat pow(Mat o, int64_t p) {
		Mat ans(o.N, o.M); ans.makeId();
		for (; p; p /= 2, o *= o) if (p&1) ans *= o;
		return ans;
	}
	friend Mat operator+(Mat a, const Mat& b) { return a += b; }
	friend Mat operator-(Mat a, const Mat& b) { return a -= b; }
	friend Mat operator*(Mat a, const Mat& b) { return a *= b; }
};