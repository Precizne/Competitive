#include <bits/stdc++.h>
#include "../../src/main.cpp"

using namespace std;

// Graph

class Graph {
public:
    ll n;
    vector<vector<ll>> adj;
    vector<bool> vst;

    Graph(ll _n) {
        n = _n;
        adj.assign(n, vector<ll>());
        vst.assign(n, false);
    }

    void add(ll u, ll v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void reset() {
        vst.assign(n, false);
    }

    // void dijkstra(ll s) {
    //     priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    //     spt[s] = 0;
    //     pq.push({0, s});
    //     while(pq.size()) {
    //         auto [d, u] = pq.top();
    //         pq.pop();
    //         if(d > spt[u]) {
    //             continue;
    //         }
    //         for(auto [v, w] : adj[u]) {
    //             if(spt[u] + w < spt[v]) {
    //                 spt[v] = spt[u] + w;
    //                 pq.push({spt[v], v});
    //             }
    //         }
    //     }
    // }

    void dfs(ll u) {
        vst[u] = true;
        for(auto v : adj[u]) {
            if(!vst[v]) {
                dfs(v);
            }
        }
        // tso.push_back(u);
    }

    // void longestPath(ll s) {
    //     for(ll u = 0; u < vtx; u++) {
    //         if(!vst[u]) {
    //             dfs(u);
    //         }
    //     }
    //     reverse(tso.begin(), tso.end());
    //     lpt[s] = 0;
    //     for(auto u : tso) {
    //         if(lpt[u] != -INF(ll)) {
    //             for(auto [v, w] : adj[u]) {
    //                 lpt[v] = max(lpt[v], lpt[u] + w);
    //             }
    //         }
    //     }
    //     for(ll i = 0; i < vtx; i++) {
    //         for(auto u : tso) {
    //             if(lpt[u] != -INF(ll)) {
    //                 for(auto [v, w] : adj[u]) {
    //                     if(lpt[v] < lpt[u] + w) {
    //                         lpt[v] = INF(ll);
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
};


// LCA

const ll LOG = 20;
vector<vector<ll>> up;
vector<ll> depth;

void dfs_lca(ll u, ll p, vector<vector<ll>> &g) {
    up[0][u] = p;
    for(ll i = 1; i < LOG; i++)
        up[i][u] = up[i - 1][ up[i - 1][u] ];
    for(ll v : g[u]) {
        if(v == p) continue;
        depth[v] = depth[u] + 1;
        dfs_lca(v, u, g);
    }
}

ll lca(ll u, ll v) {
    if(depth[u] < depth[v]) swap(u, v);
    ll k = depth[u] - depth[v];
    for(ll i = 0; i < LOG; i++)
        if(k & (1 << i))
            u = up[i][u];
    if(u == v) return u;
    for(ll i = LOG - 1; i >= 0; i--) {
        if(up[i][u] != up[i][v]) {
            u = up[i][u];
            v = up[i][v];
        }
    }
    return up[0][u];
}
