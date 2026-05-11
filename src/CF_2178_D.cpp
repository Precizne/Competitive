#include <bits/stdc++.h>

#pragma GCC optimize("O3,ffast-math,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define Precizne cin.tie(nullptr) -> sync_with_stdio(false);
#define INF(t) (is_same<t, int32_t>::value ? (int)1e9 : (long long)2e18)
#define int long long
#define uint unsigned int
#define endl "\n"

using namespace std;

void zero() {
    int n, k;
    cin >> n >> k;
    vector a(n, pair<int, int>());
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i] = { x, i + 1 };
    }
    if(k > n / 2) {
        cout << -1 << endl;
        return;
    }
    sort(a.begin(), a.end());
    if(k == 0) {
        vector<pair<int, int>> ans;
        int idx = 0;
        int v = 0;
        for(int i = 0; i < n; i++) {
            if(v >= a[i].first) {
                for(int j = idx; j < i; j++) {
                    ans.push_back({ a[j].second, a[i].second });
                }
                idx = i + 1;
                v = 0;
                continue;
            }
            v += a[i].first;
        }
        if(v) {
            cout << -1 << endl;
            return;
        }
        cout << ans.size() << endl;
        for(auto& [x, y] : ans) {
            cout << x << " " << y << endl;
        }
        return;
    }
    vector<pair<int, int>> ans;
    for(int i = 0; i < (n - 2 * k); i++) {
        ans.push_back({ a[i].second, a[i + 1].second });
    }
    for(int i = 0 ; i < k; i++) {
        ans.push_back({ a[n - 1 - i].second, a[n - 2 * k + i].second });
    }
    cout << ans.size() << endl;
    for(auto& [x, y] : ans) {
        cout << x << " " << y << endl;
    }
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
    cin >> progress;
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
