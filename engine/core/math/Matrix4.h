#pragma once

#include <cmath>
#include <cstring>
#include <iostream>
#include "Vector3.h"

namespace Pinecone {

    struct Matrix4 {
        float m[4][4]; // Row-major

        // Constructors
        Matrix4() {
            std::memset(m, 0, sizeof(m));
        }

        static Matrix4 Identity() {
            Matrix4 mat;
            mat.m[0][0] = mat.m[1][1] = mat.m[2][2] = mat.m[3][3] = 1.0f;
            return mat;
        }

        static Matrix4 Translate(const Vector3& t) {
            Matrix4 mat = Identity();
            mat.m[3][0] = t.x;
            mat.m[3][1] = t.y;
            mat.m[3][2] = t.z;
            return mat;
        }

        static Matrix4 Scale(const Vector3& s) {
            Matrix4 mat = Identity();
            mat.m[0][0] = s.x;
            mat.m[1][1] = s.y;
            mat.m[2][2] = s.z;
            return mat;
        }

        static Matrix4 RotateX(float angleRad) {
            Matrix4 mat = Identity();
            float c = std::cos(angleRad);
            float s = std::sin(angleRad);
            mat.m[1][1] = c; mat.m[1][2] = s;
            mat.m[2][1] = -s; mat.m[2][2] = c;
            return mat;
        }

        static Matrix4 RotateY(float angleRad) {
            Matrix4 mat = Identity();
            float c = std::cos(angleRad);
            float s = std::sin(angleRad);
            mat.m[0][0] = c; mat.m[0][2] = -s;
            mat.m[2][0] = s; mat.m[2][2] = c;
            return mat;
        }

        static Matrix4 RotateZ(float angleRad) {
            Matrix4 mat = Identity();
            float c = std::cos(angleRad);
            float s = std::sin(angleRad);
            mat.m[0][0] = c; mat.m[0][1] = s;
            mat.m[1][0] = -s; mat.m[1][1] = c;
            return mat;
        }

        static Matrix4 Perspective(float fov, float aspect, float zNear, float zFar) {
            Matrix4 mat;
            float tanHalfFOV = std::tan(fov / 2.0f);
            float zRange = zNear - zFar;

            mat.m[0][0] = 1.0f / (tanHalfFOV * aspect);
            mat.m[1][1] = 1.0f / tanHalfFOV;
            mat.m[2][2] = (-zNear - zFar) / zRange;
            mat.m[2][3] = 1.0f;
            mat.m[3][2] = 2.0f * zFar * zNear / zRange;

            return mat;
        }

        static Matrix4 Ortho(float left, float right, float bottom, float top, float nearZ, float farZ) {
            Matrix4 mat = Identity();
            mat.m[0][0] = 2.0f / (right - left);
            mat.m[1][1] = 2.0f / (top - bottom);
            mat.m[2][2] = -2.0f / (farZ - nearZ);
            mat.m[3][0] = -(right + left) / (right - left);
            mat.m[3][1] = -(top + bottom) / (top - bottom);
            mat.m[3][2] = -(farZ + nearZ) / (farZ - nearZ);
            return mat;
        }

        // Multiply two matrices
        Matrix4 operator*(const Matrix4& other) const {
            Matrix4 result;
            for (int r = 0; r < 4; ++r) {
                for (int c = 0; c < 4; ++c) {
                    result.m[r][c] = 
                        m[r][0] * other.m[0][c] +
                        m[r][1] * other.m[1][c] +
                        m[r][2] * other.m[2][c] +
                        m[r][3] * other.m[3][c];
                }
            }
            return result;
        }

        void Print() const {
            for (int r = 0; r < 4; ++r) {
                for (int c = 0; c < 4; ++c)
                    std::cout << m[r][c] << " ";
                std::cout << "\n";
            }
        }
    };

}
