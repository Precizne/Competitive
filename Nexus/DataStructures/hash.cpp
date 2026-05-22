#include <bits/stdc++.h>
#include "../../src/main.cpp"

using namespace std;

// ===================
// INTERFACE CONTRACT
// ===================
// template <typename T>
// concept Iterable = requires(T a, size_t i) {
//     { a.size() } -> convertible_to<size_t>;
//     { a[i] };
// };

// ============================================================
// Random Double Polynomial Rolling Prefix Hash (Entropy Hash)
// ============================================================
class EntropyHash {
public:
    template<typename Iterable>
    explicit EntropyHash(const Iterable& arr) : n(arr.size()) {
        init();

        H1.assign(n + 1, 0ll);
        H2.assign(n + 1, 0ll);

        PP1.assign(n + 1, 1ll);
        PP2.assign(n + 1, 1ll);

        for(ll i = 1; i <= n; i++) {
            PP1[i] = (ll)(((ull)PP1[i - 1] * P1) % M1);
            PP2[i] = (ll)(((ull)PP2[i - 1] * P2) % M2);

            ll h1 = H1[i - 1];
            ll h2 = H2[i - 1];

            step(h1, h2, arr[i - 1]);

            H1[i] = h1;
            H2[i] = h2;
        }
    }

    template<typename Iterable>
    static ll get(const Iterable& arr) {
        init();

        ll h1 = 0, h2 = 0;

        for(auto val : arr) {
            step(h1, h2, val);
        }

        return merge(h1, h2);
    }

    ll get(ll left, ll right) const {
        left++, right++;
        if(left > right || left < 1 || right > n) return 0;

        ll h1 = H1[right] - (ll)(((ull)H1[left - 1] * PP1[right - left + 1]) % M1);
        ll h2 = H2[right] - (ll)(((ull)H2[left - 1] * PP2[right - left + 1]) % M2);

        if(h1 < 0) h1 += M1;
        if(h2 < 0) h2 += M2;

        return merge(h1, h2);
    }

    ll get() const {
        return get(0, n - 1);
    }

private:
    static constexpr ll OFFSET = 1e9;

    static constexpr ll MIN_BASE = 2e9;
    static constexpr ll MAX_BASE = 3e9;

    static constexpr ll MIN_MOD = 3e9;
    static constexpr ll MAX_MOD = 4e9;

    static inline ll P1 = 0, P2 = 0, M1 = 0, M2 = 0;
    static inline ull FIXED_RANDOM = 0;
    static inline bool initialized = false;

    vector<ll> H1, H2, PP1, PP2;
    ll n = 0;

    static void init() {
        if(initialized) return;

        ull seed = chrono::steady_clock::now().time_since_epoch().count();
        mt19937_64 rng(seed);
        FIXED_RANDOM = rng();

        auto is_prime = [](ll num) -> bool {
            if(num < 2) return false;
            if(num == 2 || num == 3) return true;
            if(num % 2 == 0 || num % 3 == 0) return false;

            for(ll i = 5; i * i <= num; i+= 6) {
                if(num % i == 0 || num % (i + 2) == 0) return false;
            }

            return true;
        };

        auto gen_prime = [&](ll min, ll max) -> ll {
            uniform_int_distribution<ll> dist(min, max);

            while(true) {
                ll p = dist(rng);

                if(is_prime(p)) return p;
            }
        };

        P1 = gen_prime(MIN_BASE, MAX_BASE);
        P2 = gen_prime(MIN_BASE, MAX_BASE);

        while(P1 == P2) {
            P2 = gen_prime(MIN_BASE, MAX_BASE);
        }

        M1 = gen_prime(MIN_MOD, MAX_MOD);
        M2 = gen_prime(MIN_MOD, MAX_MOD);

        while(M1 == M2) {
            M2 = gen_prime(MIN_MOD, MAX_MOD);
        }

        initialized = true;
    }

    static inline void step(ll& h1, ll& h2, ll val) {
        val += OFFSET;

        h1 = (ll)(((ull)h1 * P1 + val) % M1);
        h2 = (ll)(((ull)h2 * P2 + val) % M2);
    }

    static ll merge(ll h1, ll h2) {
        ull x = ((ull)h1 << 32) | (ull)h2;

        return splitmix(x + FIXED_RANDOM);
    }

    static ull splitmix(ull x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;

        return (x ^ (x >> 31));
    }
};

// ===========================
// Rabin-Karp String Matching
// ===========================
template <typename Iterable>
vector<ll> rabin_karp(const Iterable& text, const Iterable& pattern) {
    ll n = text.size();
    ll m = pattern.size();
    vector<ll> matches;

    if(m == 0 || m > n) return matches;

    auto target_hash = EntropyHash::get(pattern);
    EntropyHash text_hash(text);

    for(ll i = 0; i < n - m + 1; i++) {
        auto window_hash = text_hash.get(i, i + m - 1);

        if(window_hash == target_hash) {
            matches.push_back(i);
        }
    }

    return matches;
}
