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

    std::vector<float> getVertices() {
        std::vector<float> vertices;
        for (const Object &obj : objects) {
            for (MyPolygon polygon : obj.polygons) {
                for (Vector3 vertex : polygon.vertices) {
                    for (float v : vertex.toArray()) {
                        vertices.emplace_back(v);
                    }
                }
            }
        }
        return vertices;
    }
};


#endif //V_3D_SCENE_H
