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
    int x, y, z, a, b, c;
    cin >> x >> y >> z >> a >> b >> c;
    int ans = 0;
    ans += min(z, c) + min(y, b) + min(x, a);
    int nz = z - min(z, c), ny = y - min(y, b), nx = x - min(x, a);
    int nc = c - min(z, c), nb = b - min(y, b), na = a - min(x, a);
    ans += min(nb, nz);
    int nnb = nb - min(nb, nz), nnz = nz - min(nb, nz);
    ans += min(na, ny + nnz);
    int nna = na - min(na, ny + nnz), nny = ny - min(na, ny + nnz), nnnz = nnz - min(na, ny + nnz);
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
