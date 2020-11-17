//
// Created by iXasthur on 14.11.2020.
//

#ifndef V_3D_SCENE_H
#define V_3D_SCENE_H

#include <vector>
#include <array>
#include <cstdlib>
#include "../object/Object.h"
#include "../light/Light.h"
#include "../camera/Camera.h"
#include "../utils/Color.h"

class Scene {
public:
    std::vector<Object> objects;
    Camera camera;
    EulerAngle eulerRotation;
    Light light;

    Color backgroundColor = Color(34, 34, 34, 255);

    Scene() = default;

    void add(const Object &obj) {
        objects.emplace_back(obj);
        reorderObjects();
    }

    void reorderObjects() {
        Vector3 pos;
        for (int i = 0; i < objects.size(); ++i) {
            if (i > 0) {
                pos.x += objects[i-1].dimension().x/2 + objects[i].dimension().x/2;
                pos.x += 1;
            }

            objects[i].position.x = pos.x;
            objects[i].position.y = pos.y;
            objects[i].position.z = pos.z;
        }
    }
};


#endif //V_3D_SCENE_H
