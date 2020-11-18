//
// Created by iXasthur on 15.11.2020.
//

#ifndef V_3D_VECTOR3_H
#define V_3D_VECTOR3_H

#include <array>
#include <cmath>

class Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {

    }

    Vector3() : x(0), y(0), z(0) {

    }

    Vector3 operator-(const Vector3 &b) const {
        Vector3 vector;
        vector.x = this->x - b.x;
        vector.y = this->y - b.y;
        vector.z = this->z - b.z;
        return vector;
    }

    Vector3 operator+(const Vector3 &b) const {
        Vector3 vector;
        vector.x = this->x - b.x;
        vector.y = this->y - b.y;
        vector.z = this->z - b.z;
        return vector;
    }

    std::array<float, 3> toArray() {
        return {x, y, z};
    }

    [[nodiscard]] float length() const {
        return std::sqrt((x * x) + (y * y) + (z * z));
    }

    void normalize() {
        float length = this->length();
        x = x / length;
        y = y / length;
        z = z / length;
    }

    [[nodiscard]] std::string toString() const {
        std::string s;

        std::string xs = std::to_string(x);
        xs = xs.substr(0, xs.find('.') + 3);

        std::string xy = std::to_string(y);
        xy = xy.substr(0, xs.find('.') + 3);

        std::string xz = std::to_string(z);
        xz = xz.substr(0, xz.find('.') + 3);

        s = "x: " + xs + " y: " + xy + " z: " + xz;
        return s;
    }

    static Vector3 cross(Vector3 v1, Vector3 v2) {
        Vector3 v;
        v.x = v1.y * v2.z - v1.z * v2.y;
        v.y = v1.z * v2.x - v1.x * v2.z;
        v.z = v1.x * v2.y - v1.y * v2.x;
        return v;
    }
};


#endif //V_3D_VECTOR3_H
