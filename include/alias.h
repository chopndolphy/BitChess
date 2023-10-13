#pragma once

// #include <vector>

// using Location = std::vector<int>;

struct Location {
    int x, y;

    Location(): x(0), y(0) {}
    Location(int x, int y): x(x), y(y) {}
    bool operator==(const Location& other) { return other.x == x && other.y == y; }
    Location& operator+=(const Location& other) { x += other.x; y += other.y; return *this; }
    Location& operator-=(const Location& other) { x -= other.x; y -= other.y; return *this; }
    Location& operator*=(const Location& other) { x *= other.x; y *= other.y; return *this; }
    Location& operator/=(const Location& other) { x /= other.x; y /= other.y; return *this; }

};