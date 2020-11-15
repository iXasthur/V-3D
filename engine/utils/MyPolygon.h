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
};


#endif //V_3D_MYPOLYGON_H
