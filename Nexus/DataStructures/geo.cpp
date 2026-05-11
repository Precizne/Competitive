#include <bits/stdc++.h>

using namespace std;

// Vec2

class Vec2 {
public:
    int x;
    int y;

    Vec2(int _x, int _y) {
        x = _x;
        y = _y;
    }

    Vec2 operator +(const Vec2& other) const {
        return {x + other.x, y + other.y};
    }

    Vec2 operator -(const Vec2& other) const {
        return {x - other.x, y - other.y};
    }

    Vec2 operator *(int k) const {
        return {x * k, y * k};
    }

    bool operator ==(const Vec2& other) const {
        return (x == other.x && y == other.y);
    }

    int cross(const Vec2& other) const {
        return (x * other.y - y * other.x);
    }

    int dot(const Vec2& other) const {
        return (x * other.x + y * other.y);
    }

    int norm2() const {
        return (x * x + y * y);
    }

    bool upper() const {
        return ((y > 0) || (y == 0 && x > 0));
    }
};

// Vec3
//
class Vec3 {
public:
    int x;
    int y;
    int z;

    Vec3(int _x, int _y, int _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    Vec3 operator +(const Vec3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vec3 operator -(const Vec3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vec3 operator *(int k) const {
        return {x * k, y * k, z * k};
    }

    bool operator ==(const Vec3& other) const {
        return (x == other.x && y == other.y && z == other.z);
    }

    int dot(const Vec3& other) const {
        return (x * other.x + y * other.y + z * other.z);
    }

    Vec3 cross(const Vec3& other) const {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }

    int norm2() const {
        return (x * x + y * y + z * z);
    }
};
