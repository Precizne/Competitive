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
    int n, m;
    cin >> n >> m;
    int c1 = 0, c2 = 0;
    for(int i = 0; i < n * m; i++) {
        int x;
        cin >> x;
        c1 += x;
    }
    for(int i = 0; i < n * m; i++) {
        int x;
        cin >> x;
        c2 += x;
    }
    if(!c1 || !c2) {
        cout << "No" << endl;
        return;
    }
    if(~(n * m) & 1) {
        cout << "Yes" << endl;
        return;
    }
    if(c1 == (n * m) || c2 == (n * m)) {
        cout << "No" << endl;
        return;
    }
    cout << "Yes" << endl;
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
