#include <bits/stdc++.h>
#include "./main.cpp"

using namespace std;

// Smallest Prime Factor

vector<ll> spf(MXN + 1);
// vector<ll> pri;

void sieve() {
    for(ll i = 0; i <= MXN; i++) {
        spf[i] = i;
    }
    for(ll i = 2; i <= MXN; i++) {
        if(spf[i] == i) {
            // pri.push_back(i);
            for(ll j = 2 * i; j <= MXN; j += i) {
                spf[j] = min(spf[j], i);
            }
        }
    }
}

// Prime Factorization

vector<ll> fvec(ll x) {
    vector<ll> f;
    while(x != 1) {
        f.push_back(spf[x]);
        x /= spf[x];
    }
    return f;
}

map<ll, ll> fmap(ll x) {
    map<ll, ll> f;
    while(x != 1) {
    f[spf[x]]++;
        x /= spf[x];
    }
    return f;
}

// String Tokenizer

vector<string> tokenize(string s, string del = " ") {
    ll start, end = -1 * del.size();
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

inline ll gcdext(ll a, ll b, ll* p, ll* q) {
    if(a == 0) {
        *p = 0;
        *q = 1;
        return b;
    }
    ll c, d;
    ll g = gcdext(b % a, a, &c, &d);
    *p = d - (b / a) * c;
    *q = c;
    return g;
}

inline ll modsum(ll a, ll b) {
    return ((a + b) % MOD + MOD) % MOD;
}

inline ll modpro(ll a, ll b) {
    return (((a % MOD) * (b % MOD)) % MOD + MOD) % MOD;
}

inline ll modexp(ll a, ll n) {
    if(n == 0) {
        return 1;
    }
    ll b= modexp(a, n / 2);
    b = modpro(b, b);
    if(n & 1) {
        b = modpro(a, b);
    }
    return (b % MOD + MOD) % MOD;
}

inline ll modinv(ll a) {
    ll b, c;
    ll g = gcdext(a, MOD, &b, &c);
    if(g != 1) {
        cerr << "ERROR: GCD DOESN'T EXIST!!! VERIFY CODE!!!" << endl;
        return 0;
    }
    return (b % MOD + MOD) % MOD;
}

// Combinatorics

vector<ll> fact(MXN + 1, 0ll);

void prec() {
    fact[0] = 1;
    for(ll i = 1; i <= MXN; i++) {
        fact[i] = modpro(fact[i - 1], i);
    }
}

inline ll nCr(ll n, ll r) {
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

vector<ll> manacher_odd(string s) {
    ll n = s.size();
    s = "$" + s + "^";
    vector<ll> p(n + 2);
    ll l = 1, r = 1;
    for(ll i = 1; i <= n; i++) {
        p[i] = max(0ll, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i];
            r = i + p[i];
        }
    }
    return vector<ll>(begin(p) + 1, end(p) - 1);
}

vector<ll> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<ll>(begin(res) + 1, end(res) - 1);
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

#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>

// FFT

const double PI = acos(-1);
typedef complex<double> cd;
namespace fft {
    void dft(vector<cd> &a, bool invert) {
        ll n = a.size();
        vector<ll> rev(n);
        for(ll i = 0, j = 0; i < n; i++) {
            if(i < j) {
                swap(a[i], a[j]);
            }
            ll bit = n >> 1;
            while(j & bit) {
                j ^= bit;
                bit >>= 1;
            }
            j ^= bit;
        }
        for(ll len = 2; len <= n; len <<= 1) {
            double angle = 2 * PI / len * (invert ? -1 : 1);
            cd wlen(cos(angle), sin(angle));
            for(ll i = 0; i < n; i += len) {
                cd w(1);
                for(ll j = 0; j < len / 2; j++) {
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

    vector<ll> convolve(vector<ll> const &a, vector<ll> const &b) {
        vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        ll n = 1;
        while (n < (ll)a.size() + (ll)b.size()) n *= 2;
        fa.resize(n);
        fb.resize(n);
        dft(fa, false);
        dft(fb, false);
        for(ll i = 0; i < n; i++) {
            fa[i] *= fb[i];
        }
        idft(fa);
        vector<ll> result(n);
        for(ll i = 0; i < n; i++) {
            result[i] = round(fa[i].real());
        }
        return result;
    }
}

// Z Algorithm

vector<ll> zfunc(string s) {
    ll n = s.size();
    vector<ll> z(n);
    ll l = 0, r = 0;
    for(ll i = 1; i < n; i++) {
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

vector<ll> pfunc(string s) {
    ll n = s.size();
    vector<ll> p(n);
    for(ll i = 1; i < n; i++) {
        ll j = p[i - 1];
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

vector<ll> kmp(string text, string pat) {
    string s = pat + "#" + text;
    vector<ll> p = pfunc(s);
    vector<ll> idx;
    ll m = pat.size();
    for(ll i = m + 1; i < (ll)s.size(); i++) {
        if(p[i] == m) {
            idx.push_back(i - 2 * m);
        }
    }
    return idx;
}
