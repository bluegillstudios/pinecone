#pragma once

#include <cmath>
#include <iostream>

namespace Pinecone {

    struct Vector3 {
        float x, y, z;

        Vector3() : x(0), y(0), z(0) {}
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

        Vector3 operator+(const Vector3& other) const {
            return { x + other.x, y + other.y, z + other.z };
        }

        Vector3 operator-(const Vector3& other) const {
            return { x - other.x, y - other.y, z - other.z };
        }

        Vector3 operator*(float scalar) const {
            return { x * scalar, y * scalar, z * scalar };
        }

        Vector3 operator/(float scalar) const {
            return { x / scalar, y / scalar, z / scalar };
        }

        float Length() const {
            return std::sqrt(x*x + y*y + z*z);
        }

        Vector3 Normalized() const {
            float len = Length();
            return len == 0 ? Vector3(0,0,0) : (*this) / len;
        }

        float Dot(const Vector3& other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        Vector3 Cross(const Vector3& other) const {
            return {
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
            };
        }

        void Print() const {
            std::cout << "Vector3(" << x << ", " << y << ", " << z << ")\n";
        }
    };

}