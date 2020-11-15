//
// Created by iXasthur on 14.11.2020.
//

#ifndef V_3D_OBJECT_H
#define V_3D_OBJECT_H

#include <vector>
#include "../utils/MyPolygon.h"

class Object {
public:
    std::vector<MyPolygon> polygons;
    Object() = default;

    void addPolygon(MyPolygon polygon) {
        polygons.emplace_back(polygon);
    }
};


#endif //V_3D_OBJECT_H
