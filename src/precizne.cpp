#include <bits/stdc++.h>

#pragma GCC optimize("O3,fast-math,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define Precizne cin.tie(nullptr) -> sync_with_stdio(false);
#define endl "\n"

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<typename T> bool chkmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<typename T> bool chkmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template<typename T> constexpr T INF = numeric_limits<T>::max() / 2;

constexpr ll MOD = 1e9 + 7;
constexpr ll MXN = 1e6 + 5;
constexpr ld EPS = 1e-9;

#ifndef ONLINE_JUDGE
#include "debug.hpp"
#else
#define dbg(...)
#endif

void zero() {
    // Do your magic here
}

int main() {
    Precizne

    cout << fixed << setprecision(16);
    cerr << fixed << setprecision(16);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    auto begin = chrono::high_resolution_clock::now();
#endif

    ll progress = 1;
    // cin >> progress;
    for(ll p = 1; p <= progress; p++) {
#ifndef ONLINE_JUDGE
        cerr << "Case #" << p << ": " << endl;
#endif
        zero();
    }

#ifndef ONLINE_JUDGE
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<ld> elapsed = end - begin;
    cerr << fixed << setprecision(6) << "Time: " << elapsed.count() << " secs" << endl;
#endif

    return 0;
}
