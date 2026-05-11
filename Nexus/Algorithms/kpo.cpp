#include <bits/stdc++.h>

using namespace std;

// Binary Grouping

vector<pair<int, int>> binaryGroup(vector<tuple<int, int, int>>& input) {
    int idx = 0;
    vector<pair<int, int>> res;
    for(auto& [v, w, k] : input) {
        int c = 1;
        while(k > c) {
            k -= c;
            res.push_back({c * v, c * w});
            c <<= 1ll;
        }
        res.push_back({k * v, k * w});
    }
    return res;
}
