//
// Created by iXasthur on 14.11.2020.
//

#ifndef V_3D_MYPOLYGON_H
#define V_3D_MYPOLYGON_H

#include <array>
#include "Vector3.h"

class MyPolygon {
public:
    std::array<Vector3, 3> vertices;

    explicit MyPolygon(std::array<Vector3, 3> vertices) {
        this->vertices = vertices;
    }

    Vector3 getNormal()
    {
        Vector3 a = vertices[0] - vertices[1];
        Vector3 b = vertices[0] - vertices[2];
        return Vector3::cross(a, b);
    }
};


#endif //V_3D_MYPOLYGON_H
