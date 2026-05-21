#include <bits/stdc++.h>
#include "../../src/main.cpp"

using namespace std;

// ===================
// INTERFACE CONTRACT
// ===================
// template <typename T>
// concept IndexableContainer = requires(T a, size_t i) {
//     { a.size() } -> convertible_to<size_t>;
//     { a[i] };
// };

// ============================================================
// Random Double Polynomial Rolling Prefix Hash (Entropy Hash)
// ============================================================
class EntropyHash {
public:
    using HashValue = pair<int, int>;

    template<typename Iterable>
    explicit EntropyHash(const Iterable& arr) : n(arr.size()) {
        init();

        H1.assign(n + 1, 0ll);
        H2.assign(n + 1, 0ll);

        PP1.assign(n + 1, 1ll);
        PP2.assign(n + 1, 1ll);

        for(int i = 2; i <= n; i++) {
            PP1[i] = (PP1[i - 1] * P1) % M1;
            PP2[i] = (PP2[i - 1] * P2) % M2;

            int h1 = H1[i - 1];
            int h2 = H2[i - 1];

            step(h1, h2, arr[i - 1]);

            H1[i] = h1;
            H2[i] = h2;
        }
    }

    template<typename Iterable>
    static HashValue get(const Iterable& arr) {
        init();

        int h1 = 0, h2 = 0;

        for(auto val: arr) {
            step(h1, h2, val);
        }

        return {h1, h2};
    }

    HashValue get(int left, int right) const {
        left++, right++;
        if(left > right || left < 1 || right > n) return {0, 0};

        int h1 = H1[right] - (H1[left - 1] * PP1[right - left + 1]) % M1;
        int h2 = H2[right] - (H2[left - 1] * PP2[right - left + 1]) % M2;

        if(h1 < 0) h1 += M1;
        if(h2 < 0) h2 += M2;

        return {h1, h2};
    }

    HashValue get() const {
        return get(0, n - 1);
    }

private:
    static constexpr int MIN_BASE = 2000000000LL;
    static constexpr int MAX_BASE = 2140000000LL;

    static constexpr int MIN_MOD = 4000000000LL;
    static constexpr int MAX_MOD = 4290000000LL;

    static inline int P1 = 0, P2 = 0, M1 = 0, M2 = 0;
    static inline bool initialized = false;

    vector<int> H1, H2, PP1, PP2;
    int n = 0;

    static void init() {
        if(initialized) return;

        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

        auto is_prime = [](int num) -> bool {
            if(num < 2) return false;
            if(num == 2 || num == 3) return true;
            if(num % 2 == 0 || num % 3 == 0) return false;

            for(int i = 5; i * i <= num; i+= 6) {
                if(num % i == 0 || num % (i + 2) == 0) return false;
            }

            return true;
        };

        auto gen_prime = [&](int min, int max) -> int {
            uniform_int_distribution<int> dist(min, max);

            while(true) {
                int p = dist(rng);

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

    static inline void step(int& h1, int& h2, int val) {
        int v1 = (val % M1 + M1) % M1;
        int v2 = (val % M2 + M2) % M2;

        h1 = (h1 * P1 + v1) % M1;
        h2 = (h2 * P2 + v2) % M2;
    }
};


// ===========================
// Rabin-Karp String Matching
// ===========================
template <typename Iterable>
vector<int> rabin_karp(const Iterable& text, const Iterable& pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> matches;

    if(m == 0 || m > n) return matches;

    auto target_hash = EntropyHash::get(pattern);
    EntropyHash text_hash(text);

    for(int i = 0; i < n - m + 1; i++) {
        auto window_hash = text_hash.get(i, i + m - 1);

        if(window_hash == target_hash) {
            matches.push_back(i);
        }
    }

    return matches;
}
