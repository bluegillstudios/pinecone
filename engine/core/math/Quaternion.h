#pragma once

#include <cmath>
#include <iostream>
#include "Vector3.h"

namespace Pinecone {

    struct Quaternion {
        float x, y, z, w;

        Quaternion() : x(0), y(0), z(0), w(1) {}
        Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        static Quaternion Identity() {
            return { 0, 0, 0, 1 };
        }

        // Create quaternion from axis-angle
        static Quaternion FromAxisAngle(const Vector3& axis, float angleRad) {
            float half = angleRad * 0.5f;
            float sinHalf = std::sin(half);
            float cosHalf = std::cos(half);
            Vector3 norm = axis.Normalized();
            return {
                norm.x * sinHalf,
                norm.y * sinHalf,
                norm.z * sinHalf,
                cosHalf
            };
        }

        // Normalize
        Quaternion Normalized() const {
            float len = std::sqrt(x * x + y * y + z * z + w * w);
            return { x / len, y / len, z / len, w / len };
        }

        // Quaternion * Quaternion (combine rotations)
        Quaternion operator*(const Quaternion& q) const {
            return {
                w * q.x + x * q.w + y * q.z - z * q.y,
                w * q.y - x * q.z + y * q.w + z * q.x,
                w * q.z + x * q.y - y * q.x + z * q.w,
                w * q.w - x * q.x - y * q.y - z * q.z
            };
        }

        // Rotate a vector using this quaternion
        Vector3 Rotate(const Vector3& v) const {
            Quaternion vq(v.x, v.y, v.z, 0);
            Quaternion result = (*this) * vq * Conjugate();
            return { result.x, result.y, result.z };
        }

        // Conjugate of the quaternion
        Quaternion Conjugate() const {
            return { -x, -y, -z, w };
        }

        // slerp
        static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t) {
            float dot = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;

            Quaternion end = b;
            if (dot < 0.0f) {
                dot = -dot;
                end = { -b.x, -b.y, -b.z, -b.w };
            }

            if (dot > 0.9995f) {
                // Linear interpolation fallback
                Quaternion result = {
                    a.x + t * (end.x - a.x),
                    a.y + t * (end.y - a.y),
                    a.z + t * (end.z - a.z),
                    a.w + t * (end.w - a.w)
                };
                return result.Normalized();
            }

            float theta = std::acos(dot);
            float sinTheta = std::sin(theta);

            float aFactor = std::sin((1.0f - t) * theta) / sinTheta;
            float bFactor = std::sin(t * theta) / sinTheta;

            return {
                a.x * aFactor + end.x * bFactor,
                a.y * aFactor + end.y * bFactor,
                a.z * aFactor + end.z * bFactor,
                a.w * aFactor + end.w * bFactor
            };
        }

        void Print() const {
            std::cout << "Quaternion(" << x << ", " << y << ", " << z << ", " << w << ")\n";
        }
    };

}