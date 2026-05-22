#include <bits/stdc++.h>
#include "../../src/main.cpp"

using namespace std;

// Disjoint Set Union

class DSU {
public:
    ll vtx;
    vector<ll> prnt, rank, size;

    DSU(ll n) {
        vtx = n;
        make(n);
    }

    void make(ll n) {
        prnt.resize(n);
        rank.resize(n, 0);
        size.resize(n, 1);
        for(ll i = 0; i < n; i++) {
            prnt[i] = i;
        }
    }

    ll find(ll u) {
        if(u == prnt[u]) {
            return u;
        }
        return prnt[u] = find(prnt[u]);
    }

    void unionRank(ll u, ll v) {
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

    void unionSize(ll u, ll v) {
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
