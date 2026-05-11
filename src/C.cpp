#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define Precizne cin.tie(nullptr) -> sync_with_stdio(false);
#define INF(t) (is_same<t, int32_t>::value ? (int)1e9 : (long long)2e18)
#define int long long
#define uint unsigned int
#define endl "\n"

using namespace std;

int solve(vector<int>& a, vector<bool>& b, unordered_map<vector<bool>, int>& dp, int n) {
    if(dp.count(b)) {
        return dp[b];
    }
    vector<int> idx;
    int c = 0;
    for(int i = 0; i < n && c < 3; i++) {
        if(!b[i]) {
            idx.push_back(i);
            c++;
        }
    }
    if(c < 3) {
        int ans = 0;
        for(auto& i : idx) {
            ans = max(ans, a[i]);
        }
        return ans;
    }
    // Case 1
    b[idx[0]] = true;
    b[idx[1]] = true;
    int ans1 = solve(a, b, dp, n) + max(a[idx[0]], a[idx[1]]);
    b[idx[0]] = false;
    b[idx[1]] = false;

    // Case 2
    b[idx[1]] = true;
    b[idx[2]] = true;
    int ans2 = solve(a, b, dp, n) + max(a[idx[1]], a[idx[2]]);
    b[idx[1]] = false;
    b[idx[2]] = false;

    // Case 3
    b[idx[0]] = true;
    b[idx[2]] = true;
    int ans3 = solve(a, b, dp, n) + max(a[idx[0]], a[idx[2]]);
    b[idx[0]] = false;
    b[idx[2]] = false;

    return dp[b] = min({ans1, ans2, ans3}); 
}

int minCost(vector<int>& a) {
    int n = a.size();
    vector b(n, false);
    unordered_map<vector<bool>, int> dp;
    return solve(a, b, dp, n);
}

void zero() {
    vector<int> a = {2, 1, 3, 3};
    cout << minCost(a) << endl;
}

signed main() {
    Precizne

    #ifndef ONLINE_JUDGE
        auto begin = chrono::high_resolution_clock::now();
        freopen("input.txt", "r", stdin); 
        freopen("output.txt", "w", stdout);
        freopen("error.txt", "w", stderr);
    #endif
        
    int progress = 1;
    // cin >> progress;
    for(int p = 1; p <= progress; p++) {
        #ifndef ONLINE_JUDGE
            cerr << "Case #" << p << ": " << endl;
        #endif
        zero();
    }

    #ifndef ONLINE_JUDGE
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        cerr << fixed << "Time: " << elapsed.count() * 1e-9 << " secs" << endl;
    #endif

    return 0;
}
