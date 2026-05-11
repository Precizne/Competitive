// Next Greater Element

vector<int> nge(vector<int> &a) {
    int n = a.size();
    vector<int> res(n, -1);
    stack<int> st;
    for(int i = 0; i < n; i++) {
        while(!st.empty() && a[st.top()] < a[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return res;
}

// Topological Sort (Kahn)

vector<int> topo_sort(int n, vector<vector<int>> &g) {
    vector<int> indeg(n), order;
    for(int u = 0; u < n; u++)
        for(int v : g[u])
            indeg[v]++;
    queue<int> q;
    for(int i = 0; i < n; i++)
        if(indeg[i] == 0)
            q.push(i);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for(int v : g[u]) {
            if(--indeg[v] == 0)
                q.push(v);
        }
    }
    return order;
}

// Floyd Cycle Detection

int find_cycle_start(vector<int> &nxt, int src) {
    int slow = src, fast = src;
    do {
        slow = nxt[slow];
        fast = nxt[nxt[fast]];
    } while(slow != fast);
    slow = src;
    while(slow != fast) {
        slow = nxt[slow];
        fast = nxt[fast];
    }
    return slow;
}
// Matrix Exponentiation (2x2)

struct mat {
    long long a[2][2];
};

mat mul(mat x, mat y, long long mod) {
    mat r{};
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            for(int k = 0; k < 2; k++)
                r.a[i][j] = (r.a[i][j] + x.a[i][k] * y.a[k][j]) % mod;
    return r;
}

mat mpow(mat a, long long e, long long mod) {
    mat r{{{1,0},{0,1}}};
    while(e) {
        if(e & 1) r = mul(r, a, mod);
        a = mul(a, a, mod);
        e >>= 1;
    }
    return r;
}

// RNG

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

long long rnd(long long l, long long r) {
    return uniform_int_distribution<long long>(l, r)(rng);
}

// Aho–Corasick

struct aho {
    static const int A = 26;
    vector<array<int, A>> nxt;
    vector<int> link, out;

    aho() {
        nxt.push_back({});
        nxt[0].fill(-1);
        link.push_back(0);
        out.push_back(0);
    }

    void insert(string s) {
        int v = 0;
        for(char c : s) {
            int x = c - 'a';
            if(nxt[v][x] == -1) {
                nxt[v][x] = nxt.size();
                nxt.push_back({});
                nxt.back().fill(-1);
                link.push_back(0);
                out.push_back(0);
            }
            v = nxt[v][x];
        }
        out[v]++;
    }

    void build() {
        queue<int> q;
        for(int c = 0; c < A; c++) {
            int u = nxt[0][c];
            if(u != -1) q.push(u);
            else nxt[0][c] = 0;
        }
        while(!q.empty()) {
            int v = q.front(); q.pop();
            out[v] += out[link[v]];
            for(int c = 0; c < A; c++) {
                int u = nxt[v][c];
                if(u != -1) {
                    link[u] = nxt[link[v]][c];
                    q.push(u);
                } else {
                    nxt[v][c] = nxt[link[v]][c];
                }
            }
        }
    }

    int match(string s) {
        int v = 0, res = 0;
        for(char c : s) {
            v = nxt[v][c - 'a'];
            res += out[v];
        }
        return res;
    }
};

// Heavy Light Decomposition

vector<int> parent, depth, heavy, head, pos, sz;
int cur_pos;

int dfs_hld(int v, vector<vector<int>> &g) {
    sz[v] = 1;
    int mx = 0;
    for(int u : g[v]) {
        if(u == parent[v]) continue;
        parent[u] = v;
        depth[u] = depth[v] + 1;
        int usz = dfs_hld(u, g);
        sz[v] += usz;
        if(usz > mx) {
            mx = usz;
            heavy[v] = u;
        }
    }
    return sz[v];
}

void decompose(int v, int h, vector<vector<int>> &g) {
    head[v] = h;
    pos[v] = cur_pos++;
    if(heavy[v] != -1)
        decompose(heavy[v], h, g);
    for(int u : g[v]) {
        if(u == parent[v] || u == heavy[v]) continue;
        decompose(u, u, g);
    }
}

// Persistent Segment Tree

struct pst {
    struct node {
        int l, r;
        long long val;
    };

    vector<node> t;
    int n;

    pst(int n) : n(n) {
        t.push_back({0, 0, 0}); // dummy
    }

    int new_node(int l, int r, long long val) {
        t.push_back({l, r, val});
        return t.size() - 1;
    }

    int build(int l, int r) {
        if(l == r)
            return new_node(0, 0, 0);
        int m = (l + r) / 2;
        int L = build(l, m);
        int R = build(m + 1, r);
        return new_node(L, R, 0);
    }

    int upd(int v, int l, int r, int pos, long long val) {
        if(l == r)
            return new_node(0, 0, val);
        int m = (l + r) / 2;
        int L = t[v].l, R = t[v].r;
        if(pos <= m)
            L = upd(L, l, m, pos, val);
        else
            R = upd(R, m + 1, r, pos, val);
        return new_node(L, R, t[L].val + t[R].val);
    }

    long long qry(int v, int l, int r, int ql, int qr) {
        if(v == 0 || qr < l || r < ql)
            return 0;
        if(ql <= l && r <= qr)
            return t[v].val;
        int m = (l + r) / 2;
        return qry(t[v].l, l, m, ql, qr)
             + qry(t[v].r, m + 1, r, ql, qr);
    }
};
