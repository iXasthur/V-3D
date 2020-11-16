//
// Created by iXasthur on 15.11.2020.
//

#ifndef V_3D_OBJECTFACTORY_H
#define V_3D_OBJECTFACTORY_H

#include "Object.h"
#include "ObjectLoader.h"

class ObjectFactory {
public:
    static Object monkey() {
        return ObjectLoader::LoadObjModel("objects/monkey.obj");
    }

    static Object pyramid() {
        return ObjectLoader::LoadObjModel("objects/pyramid.obj");
    }

    static Object spaceship() {
        return ObjectLoader::LoadObjModel("objects/spaceship.obj");
    }

    static Object cube() {
        return ObjectLoader::LoadObjModel("objects/cube.obj");
    }
};


#endif //V_3D_OBJECTFACTORY_H
