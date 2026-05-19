#include <bits/stdc++.h>

using namespace std;

int lis(const vector<int>& A) {
    vector<int> dp;

    for(auto& a : A) {
        auto it = lower_bound(dp.begin(), dp.end(), a);

        if(it == dp.end()) {
            dp.push_back(a);
        }
        else {
            *it = a;
        }
    }

    return dp.size();
}
