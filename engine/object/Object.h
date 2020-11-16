//
// Created by iXasthur on 14.11.2020.
//

#ifndef V_3D_OBJECT_H
#define V_3D_OBJECT_H

#include <vector>
#include "../utils/MyPolygon.h"
#include "../utils/Color.h"

class Object {
public:
    Vector3 position;
    std::vector<MyPolygon> polygons;

    Color color = Color(255, 255, 255, 255);

    Object() = default;

    void addPolygon(MyPolygon polygon) {
        polygons.emplace_back(polygon);
    }

    std::vector<float> getVertices() {
        std::vector<float> vertices;
        for (MyPolygon polygon : polygons) {
            for (Vector3 vertex : polygon.vertices) {
                for (float v : vertex.toArray()) {
                    vertices.emplace_back(v);
                }
            }
        }
        return vertices;
    }

    std::vector<float> getNormals() {
        std::vector<float> normals;
        for (MyPolygon polygon : polygons) {
            Vector3 normal = polygon.getNormal();
            for (int i = 0; i < polygon.vertices.size(); ++i) {
                for (float n : normal.toArray()) {
                    normals.emplace_back(n);
                }
            }
        }
        return normals;
    }
};


#endif //V_3D_OBJECT_H
