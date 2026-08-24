// https://www.spoj.com/problems/ATEXTART/en/

#include <bits/stdc++.h>

using namespace std;

void solve() {
	char x; cin >> x;
	
	string art = {"# # # # # # # # # # #         # # # # # # # # # # #\n            #    #     ##                    #    #\n          # # #  #   #    #                  # #  #\n        #   #  # #  #      #                 #  # #\n      #     #    #   ######                  #    #\n    #       #    #  #                        #    #\n      #     #    #    #            #     #   #    #\n        #   #    #      #        #  #  #  #  #    #\n          # #    #        #     #     #    # #    #\n            #    #          #  #             #    #\n"};

	for (auto& c: art) {
		if (c == '#') c = x;
	}
	cout << art << "\n";
}

int32_t main() {
	cin.tie(0)->sync_with_stdio(0);

	solve();
}