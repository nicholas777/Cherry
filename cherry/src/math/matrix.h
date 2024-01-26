#pragma once

#include "vector.h"

namespace Cherry {
    template<typename T>
    class Matrix2x2
    {
        typedef Vector2<T> vec_type;
        typedef Matrix2x2<T> type;

    protected:
        vec_type columns[2];
    public:

        Matrix2x2() {
            columns[0] = vec_type();
            columns[1] = vec_type();
        }

        Matrix2x2(float m00, float m01, float m10, float m11) {
            columns[0] = vec_type(m00, m10);
            columns[1] = vec_type(m01, m11);
        }

        Matrix2x2(vec_type m0, vec_type m1) {
            columns[0] = m0;
            columns[1] = m1;
        }

        Matrix2x2(float value) {
            columns[0] = vec_type(value, 0);
            columns[1] = vec_type(0, value);
        }

        float* ToArray() const {
            float* value = new float[4];

            value[0] = columns[0][0];
            value[1] = columns[0][1];
            value[2] = columns[1][0];
            value[3] = columns[1][1];

            return value;
        }

        static type Identity() { return type(1, 0, 0, 1); }

        void SetIdentity() {
            columns[0].x = 1;
            columns[0].y = 0;

            columns[1].x = 0;
            columns[1].y = 1;
        }

        vec_type GetRow(int index) const { return vec_type(columns[0][index], columns[1][index]); }

        vec_type GetColumn(int index) const { return columns[index]; }

        bool operator==(const type& other) const {
            return columns[0] == other[0] && columns[1] == other[1];
        }

        bool operator!=(const type& other) const {
            return !(columns[0] == other[0] && columns[1] == other[1]);
        }

        vec_type& operator[](int index) const { return columns[index]; }

        // Addition

        type operator+(const T& num) const { return type(columns[0] + num, columns[1] + num); }

        type operator+(const type& mat) const {
            return type(columns[0] + mat[0], columns[1] + mat[1]);
        }

        void operator+=(const T& num) {
            columns[0] += num;
            columns[1] += num;
        }

        void operator+=(const type& mat) {
            columns[0] += mat[0];
            columns[1] += mat[1];
        }

        // Subtraction

        type operator-(const T& num) const { return type(columns[0] - num, columns[1] - num); }

        type operator-(const type& mat) const {
            return type(columns[0] - mat[0], columns[1] - mat[1]);
        }

        void operator-=(const T& num) {
            columns[0] -= num;
            columns[1] -= num;
        }

        void operator-=(const type& mat) {
            columns[0] -= mat[0];
            columns[1] -= mat[1];
        }

        // Multiplication

        type operator*(const T& num) const { return type(columns[0] * num, columns[1] * num); }

        vec_type operator*(vec_type vec) const { return columns[0] * vec[0] + columns[1] * vec[1]; }

        type operator*(const type& Mat) const {
            return type(columns[0][0] * Mat[0][0] + columns[1][0] * Mat[0][1],
                        columns[0][1] * Mat[0][0] + columns[1][1] * Mat[0][1],
                        columns[0][0] * Mat[1][0] + columns[1][0] * Mat[1][1],
                        columns[0][1] * Mat[1][0] + columns[1][1] * Mat[1][1]);
        }

        void operator*=(const T& other) {
            columns[0] *= other;
            columns[1] *= other;
        }

        void operator*=(const type& other) {
            type mat = *this * other;
            columns[0] = mat[0];
            columns[1] = mat[1];
        }
    };

    template<typename T>
    class Matrix3x3
    {
        typedef Matrix3x3<T> type;
        typedef Vector3<T> vec_type;

    protected:
        vec_type columns[3];
    public:
        Matrix3x3() {
            columns[0] = vec_type();
            columns[1] = vec_type();
            columns[2] = vec_type();
        }

        Matrix3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20,
                  float m21, float m22) {
            columns[0] = vec_type(m00, m10, m20);
            columns[1] = vec_type(m01, m11, m21);
            columns[2] = vec_type(m02, m12, m22);
        }

        Matrix3x3(vec_type m0, vec_type m1, vec_type m2) {
            columns[0] = m0;
            columns[1] = m1;
            columns[2] = m2;
        }

        Matrix3x3(float value) {
            columns[0] = vec_type(value, 0, 0);
            columns[1] = vec_type(0, value, 0);
            columns[2] = vec_type(0, 0, value);
        }

        float* ToArray() const {
            float* value = new float[9];

            value[0] = columns[0][0];
            value[1] = columns[0][1];
            value[2] = columns[0][2];
            value[3] = columns[1][0];
            value[4] = columns[1][1];
            value[5] = columns[1][2];
            value[6] = columns[2][0];
            value[7] = columns[2][1];
            value[8] = columns[2][2];

            return value;
        }

        static type Identity() { return type(1, 0, 0, 0, 1, 0, 0, 0, 1); }

        void SetIdentity() {
            columns[0].x = 1;
            columns[0].y = 0;
            columns[0].z = 0;

            columns[1].x = 0;
            columns[1].y = 1;
            columns[1].z = 0;

            columns[2].x = 0;
            columns[2].y = 0;
            columns[2].z = 1;
        }

        vec_type GetRow(int index) const {
            return vec_type(columns[0][index], columns[1][index], columns[2][index]);
        }

        vec_type GetColumn(int index) const { return columns[index]; }

        vec_type& operator[](int index) const { return columns[index]; }

        bool operator==(const type& other) const {
            return columns[0] == other[0] && columns[1] == other[1] && columns[2] == other[2];
        }

        bool operator!=(const type& other) const {
            return !(columns[0] == other[0] && columns[1] == other[1] && columns[2] == other[2]);
        }

        // Addition

        type operator+(const T& num) const {
            return type(columns[0] + num, columns[1] + num, columns[2] + num);
        }

        type operator+(const type& mat) const {
            return type(columns[0] + mat[0], columns[1] + mat[1], columns[2] + mat[2]);
        }

        void operator+=(const T& other) {
            columns[0] += other;
            columns[1] += other;
            columns[2] += other;
        }

        void operator+=(const type& other) {
            columns[0] += other[0];
            columns[1] += other[1];
            columns[2] += other[2];
        }

        type operator-(const T& other) const {
            return type(columns[0] - other, columns[1] - other, columns[2] - other);
        }

        type operator-(const type& other) const {
            return type(columns[0] - other[0], columns[1] - other[1], columns[2] - other[2]);
        }

        void operator-=(const T& other) {
            columns[0] -= other;
            columns[1] -= other;
            columns[2] -= other;
        }

        void operator-=(const type& other) {
            columns[0] -= other[0];
            columns[1] -= other[1];
            columns[2] -= other[2];
        }

        type operator*(const T& other) const {
            return type(columns[0] * other, columns[1] * other, columns[2] * other);
        }

        vec_type operator*(vec_type vec) const {
            return columns[0] * vec[0] + columns[1] * vec[1] + columns[2] * vec[2];
        }

        type operator*(const type& other) const {
            T SrcA00 = (*this)[0][0];
            T SrcA01 = (*this)[0][1];
            T SrcA02 = (*this)[0][2];
            T SrcA10 = (*this)[1][0];
            T SrcA11 = (*this)[1][1];
            T SrcA12 = (*this)[1][2];
            T SrcA20 = (*this)[2][0];
            T SrcA21 = (*this)[2][1];
            T SrcA22 = (*this)[2][2];

            T SrcB00 = other[0][0];
            T SrcB01 = other[0][1];
            T SrcB02 = other[0][2];
            T SrcB10 = other[1][0];
            T SrcB11 = other[1][1];
            T SrcB12 = other[1][2];
            T SrcB20 = other[2][0];
            T SrcB21 = other[2][1];
            T SrcB22 = other[2][2];

            type Result;

            Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02;
            Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02;
            Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01 + SrcA22 * SrcB02;
            Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12;
            Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12;
            Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11 + SrcA22 * SrcB12;
            Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21 + SrcA20 * SrcB22;
            Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21 + SrcA21 * SrcB22;
            Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21 + SrcA22 * SrcB22;

            return Result;
        }

        void operator*=(const T& other) {
            columns[0] *= other;
            columns[1] *= other;
            columns[2] *= other;
        }

        void operator*=(const type& other) {
            type mat = *this * other;
            columns[0] *= mat[0];
            columns[1] *= mat[1];
            columns[2] *= mat[2];
        }
    };

    template<typename T>
    class Matrix4x4
    {
        typedef Matrix4x4<T> type;
        typedef Vector4<T> vec_type;

    protected:
        vec_type columns[4];
    public:
        Matrix4x4() {
            columns[0] = vec_type();
            columns[1] = vec_type();
            columns[2] = vec_type();
            columns[3] = vec_type();
        }

        Matrix4x4(float m00, float m01, float m02, float m03, float m10, float m11, float m12,
                  float m13, float m20, float m21, float m22, float m23, float m30, float m31,
                  float m32, float m33) {
            columns[0] = vec_type(m00, m10, m20, m30);
            columns[1] = vec_type(m01, m11, m21, m31);
            columns[2] = vec_type(m02, m12, m22, m32);
            columns[3] = vec_type(m03, m13, m23, m33);
        }

        Matrix4x4(const vec_type& m0, const vec_type& m1, const vec_type& m2, const vec_type& m3) {
            columns[0] = m0;
            columns[1] = m1;
            columns[2] = m2;
            columns[3] = m3;
        }

        Matrix4x4(float value) {
            columns[0] = vec_type(value, 0, 0, 0);
            columns[1] = vec_type(0, value, 0, 0);
            columns[2] = vec_type(0, 0, value, 0);
            columns[3] = vec_type(0, 0, 0, value);
        }

        T* Data() { return &columns[0].x; }

        const T* Data() const { return &columns[0].x; }

        float* ToArray() const {
            float* value = new float[16];

            value[0] = columns[0][0];
            value[1] = columns[0][1];
            value[2] = columns[0][2];
            value[3] = columns[0][3];
            value[4] = columns[1][0];
            value[5] = columns[1][1];
            value[6] = columns[1][2];
            value[7] = columns[1][3];
            value[8] = columns[2][0];
            value[9] = columns[2][1];
            value[10] = columns[2][2];
            value[11] = columns[2][3];
            value[12] = columns[3][0];
            value[13] = columns[3][1];
            value[14] = columns[3][2];
            value[15] = columns[3][3];

            return value;
        }

        static type Identity() { return type(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); }

        void SetIdentity() {
            columns[0].x = 1;
            columns[0].y = 0;
            columns[0].z = 0;
            columns[0].w = 0;

            columns[1].x = 0;
            columns[1].y = 1;
            columns[1].z = 0;
            columns[1].w = 0;

            columns[2].x = 0;
            columns[2].y = 0;
            columns[2].z = 1;
            columns[2].w = 0;

            columns[3].x = 0;
            columns[3].y = 0;
            columns[3].z = 0;
            columns[3].w = 1;
        }

        vec_type GetRow(int index) {
            return vec_type(columns[0][index], columns[1][index], columns[2][index],
                            columns[3][index]);
        }

        const vec_type GetRow(int index) const {
            return vec_type(columns[0][index], columns[1][index], columns[2][index],
                            columns[3][index]);
        }

        vec_type& GetColumn(int index) { return columns[index]; }

        const vec_type& GetColumn(int index) const { return columns[index]; }

        vec_type& operator[](int index) { return columns[index]; }

        const vec_type& operator[](int index) const { return columns[index]; }

        bool operator==(const type& other) const {
            return columns[0] == other[0] && columns[1] == other[1] && columns[2] == other[2] &&
                   columns[3] == other[3];
        }

        bool operator!=(const type& other) const {
            return !(columns[0] == other[0] && columns[1] == other[1] && columns[2] == other[2] &&
                     columns[3] == other[3]);
        }

        type operator+(const T& other) const {
            return type(columns[0] + other, columns[1] + other, columns[2] + other,
                        columns[3] + other);
        }

        type operator+(const type& other) const {
            return type(columns[0] + other[0], columns[1] + other[1], columns[2] + other[2],
                        columns[3] + other[3]);
        }

        void operator+=(const T& other) {
            columns[0] += other;
            columns[1] += other;
            columns[2] += other;
            columns[3] += other;
        }

        void operator+=(const type& other) {
            columns[0] += other[0];
            columns[1] += other[1];
            columns[2] += other[2];
            columns[3] += other[3];
        }

        type operator-(const T& other) const {
            return type(columns[0] - other, columns[1] - other, columns[2] - other,
                        columns[3] - other);
        }

        type operator-(const type& other) const {
            return type(columns[0] - other[0], columns[1] - other[1], columns[2] - other[2],
                        columns[3] - other[3]);
        }

        void operator-=(const type& other) {
            columns[0] -= other[0];
            columns[1] -= other[1];
            columns[2] -= other[2];
            columns[3] -= other[3];
        }

        void operator-=(const T& other) {
            columns[0] -= other;
            columns[1] -= other;
            columns[2] -= other;
            columns[3] -= other;
        }

        type operator*(const T& other) const {
            return type(columns[0] * other, columns[1] * other, columns[2] * other,
                        columns[3] * other);
        }

        vec_type operator*(const vec_type& other) const {
            return columns[0] * other[0] + columns[1] * other[1] + columns[2] * other[2] +
                   columns[3] * other[3];
        }

        type operator*(const type& other) const {
            type Result;
            Result[0] = columns[0] * other[0][0] + columns[1] * other[0][1] +
                        columns[2] * other[0][2] + columns[3] * other[0][3];
            Result[1] = columns[0] * other[1][0] + columns[1] * other[1][1] +
                        columns[2] * other[1][2] + columns[3] * other[1][3];
            Result[2] = columns[0] * other[2][0] + columns[1] * other[2][1] +
                        columns[2] * other[2][2] + columns[3] * other[2][3];
            Result[3] = columns[0] * other[3][0] + columns[1] * other[3][1] +
                        columns[2] * other[3][2] + columns[3] * other[3][3];
            return Result;
        }

        void operator*=(const T& other) {
            columns[0] *= other;
            columns[1] *= other;
            columns[2] *= other;
            columns[3] *= other;
        }

        void operator*=(const type& other) {
            type mat = *this * other;

            columns[0] += mat[0];
            columns[1] += mat[1];
            columns[2] += mat[2];
            columns[3] += mat[3];
        }
    };

    typedef Matrix2x2<float> Matrix2x2f;
    typedef Matrix2x2<int> Matrix2x2i;
    typedef Matrix2x2<std::uint32_t> Matrix2x2ui;
    typedef Matrix2x2<double> Matrix2x2d;

    typedef Matrix3x3<float> Matrix3x3f;
    typedef Matrix3x3<int> Matrix3x3i;
    typedef Matrix3x3<std::uint32_t> Matrix3x3ui;
    typedef Matrix3x3<double> Matrix3x3d;

    typedef Matrix4x4<float> Matrix4x4f;
    typedef Matrix4x4<int> Matrix4x4i;
    typedef Matrix4x4<std::uint32_t> Matrix4x4ui;
    typedef Matrix4x4<double> Matrix4x4d;
}
