// Sparse Table

class SparseTable {
public:
    int n, lg;
    vector<vector<int>> st;

    SparseTable(vector<int> &a) {
        n = a.size();
        lg = 32 - __builtin_clz(n);
        st.assign(lg, vector<int>(n));
        st[0] = a;
        for(int k = 1; k < lg; k++) {
            for(int i = 0; i + (1 << k) <= n; i++) {
                st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int query(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
