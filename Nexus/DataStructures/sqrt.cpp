#include <bits/stdc++.h>
#include "../../src/main.cpp"

using namespace std;

// ===================
// INTERFACE CONTRACT
// ===================
// template<typename T>
// concept SqrtConfig = requires(typename T::Element e, typename T::BlockData b,
//                               typename T::Lazy l, typename T::QueryAns qa, typename T::QueryParam qp) {
//     { T::Lazy::identity() } -> same_as<typename T::Lazy>;
//     { T::QueryAns::identity() } -> same_as<typename T::QueryAns>;
//     { l == T::Lazy::identity() } -> convertible_to<bool>;
//
//     { T::build(const vector<Element>&, ll, ll) } -> same_as<typename T::BlockData>;
//
//     { T::applyFull(b, l, l) } -> void;
//     { T::applyPartial(e, l) } -> void;
//
//     { T::queryFull(b, l, qp) } -> same_as<typename T::QueryAns>;
//     { T::queryPartial(e, l, qp) } -> same_as<typename T::QueryAns>;
//
//     { T::mergeAns(qa, qa) } -> same_as<typename T::QueryAns>;
// };

// =========================
// CORE SQRT DECOMP ENGINE
// =========================
template<class Config>
class SqrtDecomp {
    using Element = typename Config::Element;
    using BlockData = typename Config::BlockData;
    using Lazy = typename Config::Lazy;
    using QueryAns = typename Config::QueryAns;
    using QueryParam = typename Config::QueryParam;

public:
    explicit SqrtDecomp(const vector<Element>& input) {
        n = input.size();
        B = max(1LL, static_cast<ll>(sqrt(n)));
        num_blocks = (n + B - 1) / B;

        elements = input;
        blocks.resize(num_blocks);
        lazy.assign(num_blocks, Lazy::identity());

        for(ll i = 0; i < num_blocks; i++) {
            rebuild(i);
        }
    }

    void update(ll left, ll right, Lazy func) {
        ll l_block = left / B;
        ll r_block = right / B;

        if(l_block == r_block) {
            push(l_block);

            for(ll i = left; i <= right; i++) {
                Config::applyPartial(elements[i], func);
            }

            rebuild(l_block);
        }
        else {
            push(l_block);

            for (ll i = left; i < (l_block + 1) * B; i++) {
                Config::applyPartial(elements[i], func);
            }

            rebuild(l_block);

            for(ll b = l_block + 1; b < r_block; b++) {
                Config::applyFull(blocks[b], lazy[b], func);
            }

            push(r_block);

            for(ll i = r_block * B; i <= right; i++) {
                Config::applyPartial(elements[i], func);
            }

            rebuild(r_block);
        }
    }

    QueryAns query(ll left, ll right, QueryParam q) {
        ll l_block = left / B;
        ll r_block = right / B;
        QueryAns res = QueryAns::identity();

        if(l_block == r_block) {
            for(ll i = left; i <= right; i++) {
                res = Config::mergeAns(res, Config::queryPartial(elements[i], lazy[l_block], q));
            }
        }
        else {
            for(ll i = left; i < (l_block + 1) * B; i++) {
                res = Config::mergeAns(res, Config::queryPartial(elements[i], lazy[l_block], q));
            }
            for(ll b = l_block + 1; b < r_block; b++) {
                res = Config::mergeAns(res, Config::queryFull(blocks[b], lazy[b], q));
            }
            for(ll i = r_block * B; i <= right; i++) {
                res = Config::mergeAns(res, Config::queryPartial(elements[i], lazy[r_block], q));
            }
        }

        return res;
    }

private:
    ll n, B, num_blocks;
    vector<Element> elements;
    vector<BlockData> blocks;
    vector<Lazy> lazy;

    inline void push(ll b) {
        if (lazy[b] == Lazy::identity()) return;

        ll start = b * B;
        ll end = min(n, start + B);

        for (ll i = start; i < end; i++) {
            Config::applyPartial(elements[i], lazy[b]);
        }

        lazy[b] = Lazy::identity();
    }

    inline void rebuild(ll b) {
        ll start = b * B;
        ll end = min(n, start + B);

        blocks[b] = Config::build(elements, start, end);
    }
};

// =============================
// PLUG-AND-PLAY CONFIGURATIONS
// =============================

// 1. Range Add + Range Frequency Query
struct RAFQ {
    using Element = ll;
    using QueryParam = ll;

    struct BlockData {
        unordered_map<ll, ll> freq;
    };

    struct Lazy {
        ll add;

        static Lazy identity() {
            return Lazy{0};
        }

        bool operator==(const Lazy&) const = default;
    };

    struct QueryAns {
        ll count;

        static QueryAns identity() {
            return QueryAns{0};
        }
    };

    static BlockData build(const vector<Element>& arr, ll start, ll end) {
        BlockData b;

        for (ll i = start; i < end; i++) {
            b.freq[arr[i]]++;
        }

        return b;
    }

    static void applyFull(BlockData& b, Lazy& curLazy, const Lazy& func) {
        curLazy.add += func.add;
    }

    static void applyPartial(Element& elem, const Lazy& func) {
        elem += func.add;
    }

    static QueryAns queryFull(const BlockData& b, const Lazy& curLazy, const QueryParam& target) {
        ll adjusted_target = target - curLazy.add;
        auto it = b.freq.find(adjusted_target);

        if (it != b.freq.end()) {
            return QueryAns{it->second};
        }

        return QueryAns{0};
    }

    static QueryAns queryPartial(const Element& elem, const Lazy& curLazy, const QueryParam& target) {
        if (elem + curLazy.add == target) return QueryAns{1};

        return QueryAns{0};
    }

    static QueryAns mergeAns(const QueryAns& a, const QueryAns& b) {
        return QueryAns{a.count + b.count};
    }
};
