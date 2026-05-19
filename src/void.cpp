#include <bits/stdc++.h>

using namespace std;

// Smallest Prime Factor

const int MAXN = 1e6;
vector<int> spf(MAXN + 1);
// vector<int> pri;

void sieve() {
    for(int i = 0; i <= MAXN; i++) {
        spf[i] = i;
    }
    for(int i = 2; i <= MAXN; i++) {
        if(spf[i] == i) {
            // pri.push_back(i);
            for(int j = 2 * i; j <= MAXN; j += i) {
                spf[j] = min(spf[j], i);
            }
        }
    }
}

// Prime Factorization

vector<int> fvec(int x) {
    vector<int> f;
    while(x != 1) {
        f.push_back(spf[x]);
        x /= spf[x];
    }
    return f;
}

map<int, int> fmap(int x) {
    map<int, int> f;
    while(x != 1) {
    f[spf[x]]++;
        x /= spf[x];
    }
    return f;
}

// String Tokenizer

vector<string> tokenize(string s, string del = " ") {
    int start, end = -1 * del.size();
    vector<string> strv;
    do {
        start = end + del.size();
        end = s.find(del, start);
        strv.push_back(s.substr(start, end - start));
    }
    while (end != -1);
    return strv;
}

// Modulus Functions

const int MOD = 1e9 + 7;

inline int gcdext(int a, int b, int* p, int* q) {
    if(a == 0) {
        *p = 0;
        *q = 1;
        return b;
    }
    int c, d;
    int g = gcdext(b % a, a, &c, &d);
    *p = d - (b / a) * c;
    *q = c;
    return g;
}

inline int modsum(int a, int b) {
    return ((a + b) % MOD + MOD) % MOD;
}

inline int modpro(int a, int b) {
    return (((a % MOD) * (b % MOD)) % MOD + MOD) % MOD;
}

inline int modexp(int a, int n) {
    if(n == 0) {
        return 1;
    }
    int b= modexp(a, n / 2);
    b = modpro(b, b);
    if(n & 1) {
        b = modpro(a, b);
    }
    return (b % MOD + MOD) % MOD;
}

inline int modinv(int a) {
    int b, c;
    int g = gcdext(a, MOD, &b, &c);
    if(g != 1) {
        cerr << "ERROR: GCD DOESN'T EXIST!!! VERIFY CODE!!!" << endl;
        return 0;
    }
    return (b % MOD + MOD) % MOD;
}

// Combinatorics

vector<int> fact(MAXN + 1, 0ll);

void prec() {
    fact[0] = 1;
    for(int i = 1; i <= MAXN; i++) {
        fact[i] = modpro(fact[i - 1], i);
    }
}

inline int nCr(int n, int r) {
    if(n < 0 || r < 0 || n < r) {
        cerr << "ERROR: COMB DOESN'T EXIST!!! VERIFY CODE!!!" << endl;
        return 0;
    }
    return modpro(
        fact[n],
        modinv(
            modpro(
                fact[n - r],
                fact[r]
            )
        )
    );
}

// Manacher Algorithm

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i];
            r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}

// n - Dimension Vector

template<class... Args>
auto vec(size_t n, Args&&... args) {
    if constexpr(sizeof...(args) == 1)
        return vector(n, args...);
    else
        return vector(n, vec(args...));
}

// Ordered Set PBDS

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

// Prefix Rolling Double Hash

pair<vector<int>, vector<int>> master_hash(vector<int>& a) {
    const int MOD1 = 1e9 + 7;
    const int MOD2 = 1e9 + 9;
    const int BASE1 = 31;
    const int BASE2 = 37;
    
    int hash1 = 0, hash2 = 0;
    int power1 = 1, power2 = 1;
    
    vector<int> prefixHash1((int)a.size()), prefixHash2((int)a.size());
    
    for(int i = 0; i < (int)a.size(); ++i) {
        hash1 = (hash1 + a[i] * power1) % MOD1;
        hash2 = (hash2 + a[i] * power2) % MOD2;

        prefixHash1[i] = hash1;
        prefixHash2[i] = hash2;

        power1 = (power1 * BASE1) % MOD1;
        power2 = (power2 * BASE2) % MOD2;
    }
    
    return {prefixHash1, prefixHash2};
}

// FFT

const double PI = acos(-1);
typedef complex<double> cd;
namespace fft {
    void dft(vector<cd> &a, bool invert) {
        int n = a.size();
        vector<int> rev(n);
        for(int i = 0, j = 0; i < n; i++) {
            if(i < j) {
                swap(a[i], a[j]);
            }
            int bit = n >> 1;
            while(j & bit) {
                j ^= bit;
                bit >>= 1;
            }
            j ^= bit;
        }
        for(int len = 2; len <= n; len <<= 1) {
            double angle = 2 * PI / len * (invert ? -1 : 1);
            cd wlen(cos(angle), sin(angle));
            for(int i = 0; i < n; i += len) {
                cd w(1);
                for(int j = 0; j < len / 2; j++) {
                    cd u = a[i + j], v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }
        if(invert) {
            for(cd &x : a) x /= n;
        }
    }

    void idft(vector<cd> &a) {
        dft(a, true);
    }

    vector<int> convolve(vector<int> const &a, vector<int> const &b) {
        vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        int n = 1;
        while (n < (int)a.size() + (int)b.size()) n *= 2;
        fa.resize(n);
        fb.resize(n);
        dft(fa, false);
        dft(fb, false);
        for(int i = 0; i < n; i++) {
            fa[i] *= fb[i];
        }
        idft(fa);
        vector<int> result(n);
        for(int i = 0; i < n; i++) {
            result[i] = round(fa[i].real());
        }
        return result;
    }
}

// Z Algorithm

vector<int> zfunc(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

// KMP Algorithm

vector<int> pfunc(string s) {
    int n = s.size();
    vector<int> p(n);
    for(int i = 1; i < n; i++) {
        int j = p[i - 1];
        while(j > 0 && s[i] != s[j]) {
            j = p[j - 1];
        }
        if(s[i] == s[j]) {
            j++;
        }
        p[i] = j;
    }
    return p;
}

vector<int> kmp(string text, string pat) {
    string s = pat + "#" + text;
    vector<int> p = pfunc(s);
    vector<int> idx;
    int m = pat.size();
    for(int i = m + 1; i < (int)s.size(); i++) {
        if(p[i] == m) {
            idx.push_back(i - 2 * m);
        }
    }
    return idx;
}
