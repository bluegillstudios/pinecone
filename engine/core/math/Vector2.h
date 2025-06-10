#pragma once

#include <cmath>
#include <iostream>

namespace Pinecone {

    struct Vector2 {
        float x, y;

        Vector2() : x(0), y(0) {}
        Vector2(float x, float y) : x(x), y(y) {}

        // Operators
        Vector2 operator+(const Vector2& other) const {
            return { x + other.x, y + other.y };
        }

        Vector2 operator-(const Vector2& other) const {
            return { x - other.x, y - other.y };
        }

        Vector2 operator*(float scalar) const {
            return { x * scalar, y * scalar };
        }

        Vector2 operator/(float scalar) const {
            return { x / scalar, y / scalar };
        }

        Vector2& operator+=(const Vector2& other) {
            x += other.x; y += other.y;
            return *this;
        }

        float Length() const {
            return std::sqrt(x * x + y * y);
        }

        Vector2 Normalized() const {
            float len = Length();
            return len == 0 ? Vector2(0, 0) : (*this) / len;
        }

        float Dot(const Vector2& other) const {
            return x * other.x + y * other.y;
        }

        void Print() const {
            std::cout << "Vector2(" << x << ", " << y << ")\n";
        }
    };

}