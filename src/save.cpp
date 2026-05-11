#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
 
#define Precizne cin.tie(nullptr) -> sync_with_stdio(false);
#define INF(t) (is_same<t, int32_t>::value ? (int)1e9 : (long long)2e18)
#define int long long
#define uint unsigned int
#define endl "\n"

using namespace std;

typedef array<array<int, 2>, 3> vec;
vec operator+(const vec& v1, const vec& v2) {
    vec v3;
    v3[0] = {max({v1[0][0], v2[0][0], v2[2][0] - v1[1][0]}), max({v1[0][1], v2[0][1], v2[2][1] - v1[1][1]})};
    v3[1] = {min(v1[1][0], v2[1][0]), min(v1[1][1], v2[1][1])};
    v3[2] = {max(v1[2][0], v2[2][0]), max(v1[2][1], v2[2][1])};
    return v3;
}

template<typename T>
class SegmentTree {
public:
    int n;
    vector<T> tree;

    SegmentTree(vector<T> arr, T id) {
        n = arr.size();
        tree.resize(2 * n, id);
        build(arr);
    }

    void build(vector<T> arr) {
        for(int i = 0; i < n; i++) {
            tree[n + i] = arr[i];
        }
        for(int i = n - 1; i > 0; i--) {
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
        }
    }

    void update(int index, T value) {
        index += n;
        tree[index] = value;
        while(index > 1) {
            index /= 2;
            tree[index] = tree[index * 2] + tree[index * 2 + 1];
        }
    }

    T query(int left, int right) {
        left += n;
        right += n;
        T result1 = tree[0];
        T result2 = tree[0];
        while(left <= right) {
            if(left % 2 == 1) {
                result1 = result1 + tree[left];
                left++;
            }
            if(right % 2 == 0) {
                result2 = tree[right] + result2;
                right--;
            }
            left /= 2;
            right /= 2;
        }
        return result1 + result2;
    }
};

void zero() {
    int n, q;
    cin >> n >> q;
    vector a(n, 0ll);
    for(auto& i : a) {
        cin >> i;
    }
    vec id({{
        {-INF(int), -INF(int)},
        {INF(int), INF(int)},
        {-INF(int), -INF(int)}
    }});
    vector<vec> v(n);
    for(int i = 0; i < n; i++) {
        v[i] = vec({{
            {0, 0},
            {a[i] - (i + 1), a[i] - (n - i - 1)},
            {a[i] - (i + 1), a[i] - (n - i - 1)}
        }});
    }
    SegmentTree<vec> stree(v, id);
    cout << max(stree.query(0, n - 1)[0][0], stree.query(0, n - 1)[0][1]) << endl;
    while(q--) {
        int idx, val;
        cin >> idx >> val;
        stree.update(idx - 1, vec({val - idx, val - idx}));
        cout << max(stree.query(0, n - 1)[0][0], stree.query(0, n - 1)[0][1]) << endl;
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
