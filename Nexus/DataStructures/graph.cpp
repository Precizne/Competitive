#include <bits/stdc++.h>

using namespace std;

// Graph

class Graph {
public:
    int n;
    vector<vector<int>> adj;
    vector<bool> vst;

    Graph(int _n) {
        n = _n;
        adj.assign(n, vector<int>());
        vst.assign(n, false);
    }

    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void reset() {
        vst.assign(n, false);
    }

    void dijkstra(int s) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        spt[s] = 0;
        pq.push({0, s});
        while(pq.size()) {
            auto [d, u] = pq.top();
            pq.pop();
            if(d > spt[u]) {
                continue;
            }
            for(auto [v, w] : adj[u]) {
                if(spt[u] + w < spt[v]) {
                    spt[v] = spt[u] + w;
                    pq.push({spt[v], v});
                }
            }
        }
    }

    void dfs(int u) {
        vst[u] = true;
        for(auto v : adj[u]) {
            if(!vst[v]) {
                dfs(v);
            }
        }
        tso.push_back(u);
    }

    void longestPath(int s) {
        for(int u = 0; u < vtx; u++) {
            if(!vst[u]) {
                dfs(u);
            }
        }
        reverse(tso.begin(), tso.end());
        lpt[s] = 0;
        for(auto u : tso) {
            if(lpt[u] != -INF(int)) {
                for(auto [v, w] : adj[u]) {
                    lpt[v] = max(lpt[v], lpt[u] + w);
                }
            }
        }
        for(int i = 0; i < vtx; i++) {
            for(auto u : tso) {
                if(lpt[u] != -INF(int)) {
                    for(auto [v, w] : adj[u]) {
                        if(lpt[v] < lpt[u] + w) {
                            lpt[v] = INF(int);
                        }
                    }
                }
            }
        }
    }
};


// LCA

const int LOG = 20;
vector<vector<int>> up;
vector<int> depth;

void dfs_lca(int u, int p, vector<vector<int>> &g) {
    up[0][u] = p;
    for(int i = 1; i < LOG; i++)
        up[i][u] = up[i - 1][ up[i - 1][u] ];
    for(int v : g[u]) {
        if(v == p) continue;
        depth[v] = depth[u] + 1;
        dfs_lca(v, u, g);
    }
}

int lca(int u, int v) {
    if(depth[u] < depth[v]) swap(u, v);
    int k = depth[u] - depth[v];
    for(int i = 0; i < LOG; i++)
        if(k & (1 << i))
            u = up[i][u];
    if(u == v) return u;
    for(int i = LOG - 1; i >= 0; i--) {
        if(up[i][u] != up[i][v]) {
            u = up[i][u];
            v = up[i][v];
        }
    }
    return up[0][u];
}

// Coordinate Compression

template<class T>
vector<int> compress(vector<T> &a) {
    vector<T> v = a;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    vector<int> res(a.size());
    for(int i = 0; i < (int)a.size(); i++)
        res[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
    return res;
}
