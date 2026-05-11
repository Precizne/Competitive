#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define Precizne cin.tie(nullptr) -> sync_with_stdio(false);
#define INF(t) (is_same<t, int32_t>::value ? (int)1e9 : (long long)2e18)
#define int long long
#define uint unsigned int
#define endl "\n"

using namespace std;

void zero() {
    int n, c;
    cin >> n >> c;
    string s;
    cin >> s;
    vector v(5, 0ll);
    for(auto& i : s) {
        v[i - 'A']++;
    }
    int sm = 1ll << 5;
    int ans = INF(int);
    for(int m = 0; m < sm; m++) {
        int a = 0, b = 0;
        for(int i = 0; i < 5; i++) {
            if(m >> i & 1) {
                a++;
            }
            else {
                b += v[i];
            }
        }
        ans = min(ans, a * c + b * (b + 1) / 2);
    }
    cout << ans << endl;
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
