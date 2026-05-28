/**
 * Description: Computes Euler Totient function
 * Time: O(N\log\log N)
 * Source: https://cp-algorithms.com/algebra/phi-function.html
*/

template<int N> struct ETF {
	int phi[N];
	ETF() {
		for (int i = 0; i < N; i++) phi[i] = i;
		for (int i = 2; i < N; i++) if (phi[i] == i) {
			for (int j = i; j < N; j += i) {
				phi[j] -= phi[j] / i;
			}
		}
	}
};