//
// Created by iXasthur on 15.11.2020.
//

#ifndef V_3D_OBJECTFACTORY_H
#define V_3D_OBJECTFACTORY_H

#include "Object.h"

class ObjectFactory {
public:
//    static Object cube() {
//        Object obj = Object();
//
//        std::array<Vector3, 3> vertices;
//
//        vertices[0] = Vector3(1, 1, -0.5);
//        vertices[1] = Vector3(1, -1, 0);
//        vertices[2] = Vector3(-1, 1, 0);
//        obj.addPolygon(MyPolygon(vertices));
//
//        vertices[0] = Vector3(-1, -1, -0.5);
//        vertices[1] = Vector3(-1, 1, 0);
//        vertices[2] = Vector3(1, -1, 0);
//        obj.addPolygon(MyPolygon(vertices));
//
//        return obj;
//    }

    static Object pyramid() {
        Object obj = Object();

        std::array<Vector3, 3> vertices;

        vertices[0] = Vector3(0, 1, 0);
        vertices[1] = Vector3(0.5, 0, 0.5);
        vertices[2] = Vector3(-0.5, 0, 0.5);
        obj.addPolygon(MyPolygon(vertices));

        vertices[0] = Vector3(0, 1, 0);
        vertices[1] = Vector3(0.5, 0, -0.5);
        vertices[2] = Vector3(0.5, 0, 0.5);
        obj.addPolygon(MyPolygon(vertices));

        vertices[0] = Vector3(0, 1, 0);
        vertices[1] = Vector3(-0.5, 0, -0.5);
        vertices[2] = Vector3(0.5, 0, -0.5);
        obj.addPolygon(MyPolygon(vertices));

        vertices[0] = Vector3(0, 1, 0);
        vertices[1] = Vector3(-0.5, 0, 0.5);
        vertices[2] = Vector3(-0.5, 0, -0.5);
        obj.addPolygon(MyPolygon(vertices));

        vertices[0] = Vector3(-0.5, 0, 0.5);
        vertices[1] = Vector3(0.5, 0, 0.5);
        vertices[2] = Vector3(0.5, 0, -0.5);
        obj.addPolygon(MyPolygon(vertices));

        vertices[0] = Vector3(-0.5, 0, 0.5);
        vertices[1] = Vector3(0.5, 0, -0.5);
        vertices[2] = Vector3(-0.5, 0, -0.5);
        obj.addPolygon(MyPolygon(vertices));

        return obj;
    }
};


#endif //V_3D_OBJECTFACTORY_H
