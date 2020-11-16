//
// Created by iXasthur on 15.11.2020.
//

#ifndef V_3D_OBJECTFACTORY_H
#define V_3D_OBJECTFACTORY_H

#include "Object.h"
#include "ObjectLoader.h"

class ObjectFactory {
public:
    static Object spaceship() {
        Object obj = Object();
        obj.polygons = ObjectLoader::LoadObjModelPolygons("objects/spaceship.obj");
        return obj;
    }
};


#endif //V_3D_OBJECTFACTORY_H
