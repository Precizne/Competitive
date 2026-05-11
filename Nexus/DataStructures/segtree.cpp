#include <bits/stdc++.h>

using namespace std;

// =======================
// USER DEFINITIONS
// =======================

// Segment value
struct Node {
    int x, y;

    Node(int x = 0, int y = 0)
        : x(x), y(y) {}

    static Node identity() {
        return Node(0, 0);
    }
};

// Merge
Node operator+(const Node& a, const Node& b) {
    return Node(
        a.x + b.x,
        a.y + b.y
    );
}

// Lazy operation
struct Lazy {
    int add;

    Lazy(int add = 0) : add(add) {}

    bool isIdentity() const { return add == 0; }
};

// Apply lazy → node
Node applyMapping(const Lazy& func, const Node& node, int len) {
    return Node(
        node.x + func.add * len,
        node.y + func.add * len
    );
}

// Compose lazy: new after old
Lazy compose(const Lazy& newer, const Lazy& older) {
    return Lazy(newer.add + older.add);
}

// Identity lazy
Lazy lazyIdentity() {
    return Lazy(0);
}

// =======================
// SEGMENT TREE
// =======================

class SegmentTree {
public:
    SegmentTree(const vector<Node>& input) {
        n = input.size();
        size = 1;

        while (size < n) {
            size <<= 1;
        }

        data.assign(2 * size, Node::identity());
        lazy.assign(size, lazyIdentity());
        segLen.assign(2 * size, 0);

        // build leaves
        for (int i = 0; i < n; i++) {
            data[size + i] = input[i];
            segLen[size + i] = 1;
        }

        // build tree
        for (int i = size - 1; i >= 1; i--) {
            data[i] = data[2 * i] + data[2 * i + 1];
            segLen[i] = segLen[2 * i] + segLen[2 * i + 1];
        }
    }

    // range update [left, right]
    void update(int left, int right, Lazy func) {
        left += size;
        right += size;

        int leftCopy = left;
        int rightCopy = right;

        pushPath(leftCopy);
        pushPath(rightCopy);

        while (left <= right) {
            if (left % 2 == 1) {
                applyNode(left, func);
                left++;
            }

            if (right % 2 == 0) {
                applyNode(right, func);
                right--;
            }

            left /= 2;
            right /= 2;
        }

        buildPath(leftCopy);
        buildPath(rightCopy);
    }

    // point update
    void update(int pos, Lazy func) {
        pos += size;
        pushPath(pos);
        applyNode(pos, func);
        buildPath(pos);
    }

    // range query [left, right]
    Node query(int left, int right) {
        left += size;
        right += size;

        pushPath(left);
        pushPath(right);

        Node resultLeft = Node::identity();
        Node resultRight = Node::identity();

        while (left <= right) {
            if (left % 2 == 1) {
                resultLeft = resultLeft + data[left];
                left++;
            }

            if (right % 2 == 0) {
                resultRight = data[right] + resultRight;
                right--;
            }

            left /= 2;
            right /= 2;
        }

        return resultLeft + resultRight;
    }

    // point query
    Node query(int pos) {
        pos += size;
        pushPath(pos);
        return data[pos];
    }

private:
    int n;
    int size;

    vector<Node> data;
    vector<Lazy> lazy;
    vector<int> segLen;

    void applyNode(int pos, const Lazy& func) {
        data[pos] = applyMapping(func, data[pos], segLen[pos]);

        if (pos < size) {
            lazy[pos] = compose(func, lazy[pos]);
        }
    }

    void push(int pos) {
        if (!lazy[pos].isIdentity()) {
            applyNode(2 * pos, lazy[pos]);
            applyNode(2 * pos + 1, lazy[pos]);
            lazy[pos] = lazyIdentity();
        }
    }

    void pushPath(int pos) {
        for (int height = __lg(size); height >= 1; height--) {
            push(pos >> height);
        }
    }

    void buildPath(int pos) {
        while (pos > 1) {
            pos >>= 1;
            data[pos] = applyMapping(lazy[pos], data[2 * pos] + data[2 * pos + 1], segLen[pos]);
        }
    }
};

// Range Add + Range Sum

namespace RARS {

// Node
struct Node {
    long long sum;

    Node(long long sum = 0)
        : sum(sum) {}

    static Node identity() {
        return Node(0);
    }
};

Node operator+(const Node& a, const Node& b) {
    return Node(a.sum + b.sum);
}

// Lazy
struct Lazy {
    long long add;
    Lazy(long long add = 0) : add(add) {}

    bool isIdentity() const { return add == 0; }
};

Node applyMapping(const Lazy& f, const Node& node, int len) {
    return Node(node.sum + f.add * len);
}

Lazy compose(const Lazy& f, const Lazy& g) {
    return Lazy(f.add + g.add);
}

Lazy lazyIdentity() {
    return Lazy(0);
}

} // namespace RARS;

// Range Add + Range Max

namespace RARM {

struct Node {
    long long mx;

    Node(long long mx = LLONG_MIN)
        : mx(mx) {}

    static Node identity() {
        return Node(LLONG_MIN);
    }
};

Node operator+(const Node& a, const Node& b) {
    return Node(max(a.mx, b.mx));
}

struct Lazy {
    long long add;
    Lazy(long long add = 0) : add(add) {}

    bool isIdentity() const { return add == 0; }
};

Node applyMapping(const Lazy& f, const Node& node, int len) {
    return Node(node.mx + f.add);
}

Lazy compose(const Lazy& f, const Lazy& g) {
    return Lazy(f.add + g.add);
}

Lazy lazyIdentity() {
    return Lazy(0);
}

} // namespace RARM;

// Range Add + Range Sum + Range Sum of Squares

namespace RASS {

struct Node {
    long long sum;
    long long sq;

    Node(long long sum = 0, long long sq = 0)
        : sum(sum), sq(sq) {}

    static Node identity() {
        return Node(0, 0);
    }
};

Node operator+(const Node& a, const Node& b) {
    return Node(
        a.sum + b.sum,
        a.sq + b.sq
    );
}

struct Lazy {
    long long add;
    Lazy(long long add = 0) : add(add) {}

    bool isIdentity() const { return add == 0; }
};

Node applyMapping(const Lazy& f, const Node& node, int len) {
    long long new_sum = node.sum + f.add * len;
    long long new_sq = node.sq + 2 * f.add * node.sum + f.add * f.add * len;

    return Node(new_sum, new_sq);
}

Lazy compose(const Lazy& f, const Lazy& g) {
    return Lazy(f.add + g.add);
}

Lazy lazyIdentity() {
    return Lazy(0);
}

} // namespace RASS;

// No Lazy + DP Transition

namespace NLDP {

// =======================
// USER DEFINITIONS
// =======================

const int INF = (int)2e18;

struct Node {
    long long m[2][2];

    Node() {
        m[0][0] = 0;   m[0][1] = INF;
        m[1][0] = INF; m[1][1] = 0;
    }

    Node(long long a) {
        m[0][0] = INF;
        m[0][1] = a;
        m[1][0] = 0;
        m[1][1] = a;
    }

    static Node identity() {
        return Node();
    }
};

Node operator+(const Node& a, const Node& b) {
    Node res;

    res.m[0][0] = res.m[0][1] = res.m[1][0] = res.m[1][1] = INF;

    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            for(int k = 0; k < 2; ++k) {
                res.m[i][j] = std::min(res.m[i][j], a.m[i][k] + b.m[k][j]);
            }
        }
    }

    return res;
}

struct Lazy {
    bool dummy;
    Lazy() : dummy(true) {}
    bool isIdentity() const { return true; }
};

// Apply lazy → node
Node applyMapping(const Lazy& func, const Node& node, int len) {
    return node;
}

// Compose lazy
Lazy compose(const Lazy& newer, const Lazy& older) {
    return Lazy();
}

// Identity lazy
Lazy lazyIdentity() {
    return Lazy();
}

} // namespace NLDP;
