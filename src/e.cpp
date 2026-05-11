#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define Precizne cin.tie(nullptr) -> sync_with_stdio(false);
#define INF(t) (is_same<t, int32_t>::value ? (int)1e9 : (long long)2e18)
#define int long long
#define uint unsigned int
#define endl "\n"

using namespace std;

class DSU {
public:
    int vtx;
    vector<int> prnt, rank, size;

    DSU(int n) {
        vtx = n;
        make(n);
    }

    void make(int n) {
        prnt.resize(n);
        rank.resize(n, 0);
        size.resize(n, 1);
        for(int i = 0; i < n; i++) {
            prnt[i] = i;
        }
    }

    int find(int u) {
        if(u == prnt[u]) {
            return u;
        }
        return prnt[u] = find(prnt[u]);
    }

    void unionRank(int u, int v) {
        u = find(u);
        v = find(v);
        if(u != v) {
            if(rank[u] > rank[v]) {
                swap(u, v);
            }
            prnt[u] = v;
            if(rank[u] == rank[v]) {
                rank[v]++;
            }
        }
    }

    void unionSize(int u, int v) {
        u = find(u);
        v = find(v);
        if(u != v) {
            if(size[u] > size[v]) {
                swap(u, v);
            }
            prnt[u] = v;
            size[v] += size[u];
        }
    }
};

void zero() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    vector<pair<int, vector<int>>> a(n);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if(dsu.find(u) == dsu.find(v)) {
            a[v].first = v;
            a[v].second.push_back(u);
        }
        else {
            dsu.unionRank(u, v);
        }
    }
    sort(a.begin(), a.end(), [&](pair<int, vector<int>>& p, pair<int, vector<int>>& q) {
        return dsu.find(p.first) < dsu.find(q.first);
    });
    vector<pair<int, int>> pow;
    vector<tuple<int, int, int>> ans;
    int p = dsu.find(a[0].first);
    for(int u = 0; u < n; u++) {
        if(dsu.find(a[u].first) != p) {
            ans.push_back({pow.back().first + 1, pow.back().second + 1, u + 1});
            pow.pop_back();
            p = dsu.find(a[u].first);
        }
        for(auto v : a[u].second) {
            pow.push_back({u, v});
        }
    }
    cout << ans.size() << endl;
    for(auto [u, v1, v2] : ans) {
        cout << u << " " << v1 << " " << v2 << endl;
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
