#include <bits/stdc++.h>
#include "../../src/main.cpp"

// ===================
// INTERFACE CONTRACT
// ===================
// template<typename T>
// concept SegmentTreeConfig = requires(typename T::Node n, typename T::Lazy l, int len) {
//     typename T::Node;
//     typename T::Lazy;
//
//     { T::Node::identity() } -> std::same_as<typename T::Node>;
//     { T::Lazy::identity() } -> std::same_as<typename T::Lazy>;
//
//     { n == T::Node::identity() } -> std::convertible_to<bool>;
//     { l == T::Lazy::identity() } -> std::convertible_to<bool>;
//
//     { T::merge(n, n) } -> std::same_as<typename T::Node>;
//     { T::compose(l, l) } -> std::same_as<typename T::Lazy>;
//     { T::apply(l, n, len) } -> std::same_as<typename T::Node>;
// };

// =========================
// CORE SEGMENT TREE ENGINE
// =========================
template<class Config>
class SegmentTree {
    using Node = typename Config::Node;
    using Lazy = typename Config::Lazy;

public:
    explicit SegmentTree(const vector<Node>& input) {
        n = input.size();
        size = bit_ceil(static_cast<unsigned int>(n));

        data.assign(2 * size, Node::identity());
        lazy.assign(size, Lazy::identity());
        segLen.assign(2 * size, 0);

        for(int i = 0; i < n; i++) {
            data[size + i] = input[i];
            segLen[size + i] = 1;
        }

        for(int i = size - 1; i >= 1; i--) {
            data[i] = Config::merge(data[2 * i], data[2 * i + 1]);
            segLen[i] = segLen[2 * i] + segLen[2 * i + 1];
        }
    }

    void update(int left, int right, Lazy func) {
        left += size;
        right += size;

        int leftCopy = left;
        int rightCopy = right;

        pushPath(leftCopy);
        pushPath(rightCopy);

        while(left <= right) {
            if(left & 1) applyNode(left++, func);
            if(!(right & 1)) applyNode(right--, func);

            left >>= 1;
            right >>= 1;
        }

        buildPath(leftCopy);
        buildPath(rightCopy);
    }

    Node query(int left, int right) {
        left += size;
        right += size;

        pushPath(left);
        pushPath(right);

        Node resultLeft = Node::identity();
        Node resultRight = Node::identity();

        while(left <= right) {
            if(left & 1) resultLeft = Config::merge(resultLeft, data[left++]);
            if(!(right & 1)) resultRight = Config::merge(data[right--], resultRight);

            left >>= 1;
            right >>= 1;
        }

        return Config::merge(resultLeft, resultRight);
    }

private:
    int n;
    int size;
    vector<Node> data;
    vector<Lazy> lazy;
    vector<int> segLen;

    inline void applyNode(int pos, const Lazy& func) {
        data[pos] = Config::apply(func, data[pos], segLen[pos]);

        if(pos < size) lazy[pos] = Config::compose(func, lazy[pos]);
    }

    inline void push(int pos) {
        if(!(lazy[pos] == Lazy::Identity())) {
            applyNode((pos << 1), lazy[pos]);
            applyNode((pos << 1) | 1, lazy[pos]);

            lazy[pos] = Lazy::identity();
        }
    }

    inline void pushPath(int pos) {
        int height = std::countr_zero(static_cast<unsigned int>(size));

        for(int h = height; h >= 1; h--) {
            push(pos >> h);
        }
    }

    inline void buildPath(int pos) {
        while(pos > 1) {
            pos >>= 1;

            data[pos] = Config::apply(
                lazy[pos],
                Config::merge(data[pos << 1], data[(pos << 1) | 1]),
                segLen[pos]
            );
        }
    }
};

// =============================
// PLUG-AND-PLAY CONFIGURATIONS
// =============================

// 1. Range Mul-Add + Range Sum
struct RMARS {
    struct Node {
        int val;

        static Node identity() {
            return Node{ 0 };
        }

        bool operator==(const Node&) const = default;
    };

    struct Lazy {
        int mul;
        int add;

        static Lazy identity() {
            return Lazy{ 1, 0 };
        }

        bool operator==(const Lazy&) const = default;
    };

    static Node merge(const Node& a, const Node& b) {
        return Node{ a.val + b.val };
    }

    static Node apply(const Lazy& f, const Node& node, int len) {
        return Node{ node.val * f.mul + f.add * len };
    }

    static Lazy compose(const Lazy& newer, const Lazy& older) {
        return Lazy{ newer.mul * older.mul, newer.mul * older.add + newer.add };
    }
};

// 2. Range Add + Range Sum
struct RARS {
    struct Node {
        int sum;

        static Node identity() {
            return Node{ 0 };
        }

        bool operator==(const Node&) const = default;
    };

    struct Lazy {
        int add;

        static Lazy identity() {
            return Lazy{ 0 };
        }

        bool operator==(const Lazy&) const = default;
    };

    static Node merge(const Node& a, const Node& b) {
        return Node{ a.sum + b.sum };
    }

    static Node apply(const Lazy& f, const Node& node, int len) {
        return Node{ node.sum + f.add * len };
    }

    static Lazy compose(const Lazy& newer, const Lazy& older) {
        return Lazy{ newer.add + older.add };
    }
};

// 3. Range Add + Range Max
struct RARM {
    struct Node {
        int mx;

        static Node identity() {
            return Node{ -INF<int> };
        }

        bool operator==(const Node&) const = default;
    };

    struct Lazy {
        int add;

        static Lazy identity() {
            return Lazy{ 0 };
        }

        bool operator==(const Lazy&) const = default;
    };

    static Node merge(const Node& a, const Node& b) {
        return Node{ max(a.mx, b.mx) };
    }

    static Node apply(const Lazy& f, const Node& node, int len) {
        if(node.mx == INF<int>) return node;

        return Node{ node.mx + f.add };
    }

    static Lazy compose(const Lazy& newer, const Lazy& older) {
        return Lazy{ newer.add + older.add };
    }
};

// 4. Range Add + Range Sum-SumOfSquares
struct RASS {
    struct Node {
        int sum;
        int sq;

        static Node identity() {
            return Node{ 0, 0 };
        }

        bool operator==(const Node&) const = default;
    };

    struct Lazy {
        int add;

        static Lazy identity() {
            return Lazy{0};
        }

        bool operator==(const Lazy&) const = default;
    };

    static Node merge(const Node& a, const Node& b) {
        return Node{ a.sum + b.sum, a.sq + b.sq };
    }

    static Node apply(const Lazy& f, const Node& node, int len) {
        int new_sum = node.sum + f.add * len;
        int new_sq = node.sq + 2LL * f.add * node.sum + f.add * f.add * len;

        return Node{ new_sum, new_sq };
    }

    static Lazy compose(const Lazy& newer, const Lazy& older) {
        return Lazy{ newer.add + older.add };
    }
};

// 5. No Lazy + DP Transition
struct NLDP {
    struct Node {
        array<array<int, 2>, 2> m;

        static Node identity() {
            return Node{{{
                { 0, INF<int> },
                { INF<int>, 0 }
            }}};
        }

        static Node fromVal(int a) {
            return Node{{{
                { INF<int>, a },
                { 0, a }
            }}};
        }

        bool operator==(const Node&) const = default;
    };

    struct Lazy {
        bool dummy;

        static Lazy identity() { return Lazy{ true }; }

        bool operator==(const Lazy&) const = default;
    };

    static Node merge(const Node& a, const Node& b) {
        Node res;

        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                res.m[i][j] = INF<int>;

                for(int k = 0; k < 2; k++) {
                    chkmin(res.m[i][j], a.m[i][k] + b.m[k][j]);
                }
            }
        }

        return res;
    }

    static Node apply(const Lazy& f, const Node& node, int len) {
        return node;
    }

    static Lazy compose(const Lazy& newer, const Lazy& older) {
        return Lazy{ true };
    }
};
