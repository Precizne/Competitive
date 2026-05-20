#include <bits/stdc++.h>

using namespace std;

template<class T>
struct CoordinateCompression {
    vector<T> vals;

    CoordinateCompression() = default;

    CoordinateCompression(const vector<T>& v) {
        build(v);
    }

    void build(const vector<T>& v) {
        vals = v;

        sort(vals.begin(), vals.end());

        vals.erase(
            unique(vals.begin(), vals.end()),
            vals.end()
        );
    }

    // Compress value -> index
    int get(const T& x) const {
        return lower_bound(
            vals.begin(),
            vals.end(),
            x
        ) - vals.begin();
    }

    // Original value from compressed index
    T rev(int idx) const {
        return vals[idx];
    }

    // Number of unique coordinates
    int size() const {
        return vals.size();
    }

    // Compress entire vector
    vector<int> compress(const vector<T>& v) const {
        vector<int> res(v.size());

        for (int i = 0; i < (int)v.size(); i++) {
            res[i] = get(v[i]);
        }

        return res;
    }
};
