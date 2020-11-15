//
// Created by iXasthur on 15.11.2020.
//

#ifndef V_3D_VECTOR3_H
#define V_3D_VECTOR3_H

#include <array>

class Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {

    }

    Vector3() : x(0), y(0), z(0) {

    }

    std::array<float, 3> toArray() {
        return {x, y, z};
    }
};


#endif //V_3D_VECTOR3_H
