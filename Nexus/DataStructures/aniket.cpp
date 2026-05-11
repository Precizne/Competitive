#include <bits/stdc++.h>

using namespace std;

struct PolyHash {
    // Using an unsigned long long hash with base.
    static const unsigned long long BASE = 131ULL; // A common base value
    vector<unsigned long long> prefix, suffix, power;
    int n;
    PolyHash(const string &s) {
        n = s.size();
        prefix.resize(n + 1, 0);
        suffix.resize(n + 2, 0);
        power.resize(n + 1, 0);
        power[0] = 1;
        for (int i = 0; i < n; i++) {
            power[i + 1] = power[i] * BASE;
        }
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] * BASE + (unsigned long long)(s[i]);
        }
        for (int i = n - 1; i >= 0; i--) {
            suffix[i + 1] = suffix[i + 2] * BASE + (unsigned long long)(s[i]);
        }
    }
    unsigned long long getFwdHash(int L, int R) {
        return prefix[R + 1] - prefix[L] * power[R - L + 1];
    }
    unsigned long long getRevHash(int L, int R) {
        return suffix[L + 1] - suffix[R + 2] * power[R - L + 1];
    }
};

class SegmentTree {
public:
    int n;
    vector<int> tree;
    char opera = '+';
    SegmentTree(vector<int> &arr, char op) {
        n = arr.size();
        tree.resize(2 * n);
        opera = op;
        build(arr);
    }
    int apply(int a, int b) {
        if (opera == '&')
            return a & b;
        if (opera == '^')
            return a ^ b;
        if (opera == '<')
            return min(a, b);
        if (opera == '>')
            return max(a, b);
        if (opera == 'c')
            return gcd();
        return a + b;
    }
    void build(vector<int> &arr) {
        for (int i = 0; i < n; i++) {
            tree[n + i] = arr[i];
        }
        for (int i = n - 1; i > 0; i--) {
            tree[i] = apply(tree[i * 2], tree[i * 2 + 1]);
        }
    }
    void update(int index, int value) {
        index += n;
        tree[index] = value;
        while (index > 1) {
            index /= 2;
            tree[index] = apply(tree[index * 2], tree[index * 2 + 1]);
        }
    }
    int query(int left, int right) {
        left += n;
        right += n;
        int result = G;
        while (left <= right) {
        if (left % 2 == 1) {
            result = apply(result, tree[left]);
            left++;
        }
        if (right % 2 == 0) {
            result = apply(result, tree[right]);
            right--;
        }
        left /= 2;
        right /= 2;
        }
        return result;
    }
};

class LazySegmentTree {
private:
    int n;
    vector<long long> tree, lazy;
    void build(vector<int> &arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }
    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node]; // Apply lazy
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    void updateRange(int l, int r, int val, int node, int start, int end) {
        push(node, start, end);
        if (r < start || l > end)
            return;
        if (l <= start && end <= r) {
            lazy[node] += val;
            push(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        updateRange(l, r, val, 2 * node + 1, start, mid);
        updateRange(l, r, val, 2 * node + 2, mid + 1, end);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
    long long queryRange(int l, int r, int node, int start, int end) {
        push(node, start, end);
        if (r < start || l > end)
            return 0;
        if (l <= start && end <= r)
            return tree[node];
        int mid = (start + end) / 2;
        long long left = queryRange(l, r, 2 * node + 1, start, mid);
        long long right = queryRange(l, r, 2 * node + 2, mid + 1, end);
        return left + right;
    }

public:
    LazySegmentTree(vector<int> &arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }
    void update(int l, int r, int val) { updateRange(l, r, val, 0, 0, n - 1); }
    long long query(int l, int r) { return queryRange(l, r, 0, 0, n - 1); }
};

class DSU {
    vector<int> parent;

public:
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int findparent(int n) {
        if (n == parent[n])
        return n;
        return parent[n] = findparent(parent[n]);
    }
    void union(int u, int v) { parent[findparent(u)] = findparent(v); }
};

class SparseTable {
private:
    vector<vector<pair<int, int>>> st;
    vector<int> log2_table;
    int n;
    pair<int, int> merge(pair<int, int> p1, pair<int, int> p2) {
        if (p1.first > p2.first)
            return p1;
        if (p1.first < p2.first)
            return p2;
        return {p1.first, min(p1.second, p2.second)};
    }

public:
    SparseTable(vector<pair<int, int>> &arr) {
        n = arr.size();
        int max_log = log2(n) + 1;
        st.assign(n, vector<pair<int, int>>(max_log));
        log2_table.resize(n + 1);
        log2_table[1] = 0;
        for (int i = 2; i <= n; i++)
            log2_table[i] = log2_table[i / 2] + 1;
        for (int i = 0; i < n; i++)
            st[i][0] = arr[i];
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = merge(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    pair<int, int> query(int L, int R) {
        int length = R - L + 1;
        int k = log2_table[length];
        return merge(st[L][k], st[R - (1 << k) + 1][k]);
    }
};

vector<int> fact(N, 1);

int binpow(int a, int b, int m) {
    a %= m;
    int res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

int modmuli(int a, int b, int p) {
    long long res = 0;
    a %= p;
    while (b) {
        if (b & 1)
            res = (res + a) % p;
        a = (2 * a) % p;
        b >>= 1;
    }
    return res;
}

int gcdExtended(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

int modInverse(int b, int m) {
    int x, y;
    int giga = gcdExtended(b, m, &x, &y);
    if (giga != 1)
        return -1;
    return (x % m + m) % m;
}

void factorial(int p) {
    for (int i = 2; i < N; i++) {
        fact[i] = modmuli(fact[i - 1], i, p);
    }
}

int nCr(int n, int r, int p) {
    if (r > n)
        return 0;
    return modmuli(fact[n], modInverse(modmuli(fact[n - r], fact[r], p), p), p);
}

int modDivide(int a, int b, int m) {
    a = a % m;
    int inv = modInverse(b, m);
    if (inv == -1)
        return 0;
    else
        return (inv * a) % m;
}

vector<int> sieve() {
    vector<int> prime(N + 1, 1);
    for (int p = 2; p * p <= N; p++) {
        if (prime[p] == true) {
            for (int i = p * p; i <= N; i += p)
                prime[i] = false;
        }
    }
    vector<int> ans;
    for (int i = 2; i <= N; i++) {
        if (prime[i]) {
            ans.push_back(i);
        }
    }
    return ans;
}

// Disjoint Set Union
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
        for (int i = 0; i < n; i++) {
            prnt[i] = i;
        }
    }
    int find(int u) {
        if (u == prnt[u]) {
            return u;
        }
        return prnt[u] = find(prnt[u]);
    }
    void unionRank(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            if (rank[u] > rank[v]) {
                swap(u, v);
            }
            prnt[u] = v;
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
        }
    }
    void unionSize(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            if (size[u] > size[v]) {
                swap(u, v);
            }
            prnt[u] = v;
            size[v] += size[u];
        }
    }
};

vector<int> spf;
void sieve() {
    spf.resize(N + 1, 1);
    spf[0] = 1;
    for (int i = 2; i <= N; i++) {
        if (spf[i] == 1) {
            for (int j = i; j <= N; j += i) {
                if (spf[j] == 1) {
                    spf[j] = i;
                }
            }
        }
    }
}

map<int, int> getFactorization(int x) {
    map<int, int> ret;
    if (x <= 0)
        return ret;
    while (x != 1) {
        ret[spf[x]]++;
        x = x / spf[x];
    }
    return ret;
}

void dijkstra(int s, vector<int> &d, vector<int> &p) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);
    d[s] = 0;
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().second;
        int d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;
        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}

template <typename T, typename U> struct LazySegmentTree {
    int n; // Size of the underlying array (rounded to next power of two)
    std::vector<T> tree; // Segment tree to store node values
    std::vector<U> lazy; // Lazy tree to store pending updates
    T identity_element;  // Identity element for query operation (e.g., 0
    for sum, INF for min)
    U identity_lazy; // Identity element for the update operation
    (e.g., 0 for addition)
    // Function to combine two segment nodes (used in queries)
    std::function<T(T, T)> combine;
    // Function to apply a lazy value to a segment node
    // Parameters: (node value, lazy value, length of the segment)
    std::function<void(T &, U, int)> apply;
    // Function to combine two lazy values (used when propagating lazily)
    std::function<U(U, U)> combine_lazy;
    /**
    * Constructor
    * @param size - size of the input array
    * @param id_elem - identity element for query (e.g., 0 for sum)
    * @param id_lazy - identity element for updates (e.g., 0 for add)
    * @param combine - how to combine two segment values (g)
    * @param apply - how to apply a lazy value to a segment
    * @param combine_lazy - how to combine two lazy values (f)
    */
    LazySegmentTree(int size, T id_elem, U id_lazy, std::function<T(T, T)> combine,
                    std::function<void(T &, U, int)> apply,
                    std::function<U(U, U)> combine_lazy)
        : identity_element(id_elem), identity_lazy(id_lazy), combine(combine),
        apply(apply), combine_lazy(combine_lazy) {
        n = 1;
        while (n < size)
            n <<= 1;
        tree.assign(2 * n, identity_element);
        lazy.assign(2 * n, identity_lazy);
    }
    // Pushes the pending lazy updates from node x to its children
    void push(int x, int lx, int rx) {
        if (lazy[x] == identity_lazy || rx - lx == 1)
            return; // Leaf or
        no pending update int mid = (lx + rx) / 2;
        apply(tree[2 * x + 1], lazy[x], mid - lx); // apply to left child
        apply(tree[2 * x + 2], lazy[x], rx - mid); // apply to right child
        lazy[2 * x + 1] = combine_lazy(lazy[2 * x + 1], lazy[x]); //accumulate
        lazy[2 * x + 2] = combine_lazy(lazy[2 * x + 2], lazy[x]);
        lazy[x] = identity_lazy; // clear current lazy value
    }
    // Internal function to apply update value `val` on range [l, r)
    void update(int l, int r, U val, int x, int lx, int rx) {
        push(x, lx, rx); // propagate any pending updates
        if (rx <= l || r <= lx)
            return;                 // no overlap
        if (l <= lx && rx <= r) { // total overlap
            apply(tree[x], val, rx - lx);
            lazy[x] = combine_lazy(lazy[x], val);
            return;
        }
        // partial overlap
        int mid = (lx + rx) / 2;
        update(l, r, val, 2 * x + 1, lx, mid);
        update(l, r, val, 2 * x + 2, mid, rx);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]); // update current node
    }
    // Public function to apply update on range [l, r)
    void update(int l, int r, U val) { update(l, r, val, 0, 0, n); }
    // Internal function to query on range [l, r)
    T query(int l, int r, int x, int lx, int rx) {
        push(x, lx, rx); // make sure values are up to date
        if (rx <= l || r <= lx)
            return identity_element; // no overlap
        if (l <= lx && rx <= r)
            return tree[x]; // total overlap
        // partial overlap
        int mid = (lx + rx) / 2;
        T s1 = query(l, r, 2 * x + 1, lx, mid);
        T s2 = query(l, r, 2 * x + 2, mid, rx);
        return combine(s1, s2); // combine results
    }
    // Public function to query on range [l, r)
    T query(int l, int r) { return query(l, r, 0, 0, n); }
    // Internal function to build segment tree from array
    void build(const std::vector<T> &arr, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)arr.size())
            tree[x] = arr[lx];
            return;
        }
        int mid = (lx + rx) / 2;
        build(arr, 2 * x + 1, lx, mid);
        build(arr, 2 * x + 2, mid, rx);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }
    // Public function to build segment tree from array
    void build(const std::vector<T> &arr) { build(arr, 0, 0, n); }
};

int main() {
    int size = 10;
    std::vector<long long> arr(size, 0);
    LazySegmentTree<long long, long long> seg(
        size,
        0LL,                                            // identity for sum
        0LL,                                            // identity for addition
        [](long long a, long long b) { return a + b; }, // combine (query)
        [](long long &node, long long lazy_val, int len) {
            node += lazy_val * len;
        },                                             // apply
        [](long long a, long long b) { return a + b; } // combine lazy
    );
    seg.build(arr);
    seg.update(2, 5, 3);                   // add 3 to range [2, 5)
    std::cout << seg.query(0, 10) << '\n'; // should print 9
}
