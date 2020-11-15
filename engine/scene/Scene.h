//
// Created by iXasthur on 14.11.2020.
//

#ifndef V_3D_SCENE_H
#define V_3D_SCENE_H

#include <vector>
#include <array>
#include <cstdlib>
#include "../object/Object.h"
#include "../camera/Camera.h"
#include "../utils/Color.h"

class Scene {
public:
    std::vector<Object> objects;
    Camera camera;

    Color backgroundColor = Color(34, 34, 34, 255);

    Scene() = default;

    void add(const Object &obj) {
        objects.emplace_back(obj);
    }
};


#endif //V_3D_SCENE_H
