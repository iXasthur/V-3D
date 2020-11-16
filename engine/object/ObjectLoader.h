//
// Created by iXasthur on 16.11.2020.
//

#ifndef V_3D_OBJECTLOADER_H
#define V_3D_OBJECTLOADER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include "Object.h"

class ObjectLoader {
public:
    static std::vector<Vector3> LoadObjModelVertices(const char *filename) {
        std::ifstream in(filename, std::ios::in);
        if (!in) {
            std::cerr << "Cannot open " << filename << std::endl;
            exit(1);
        }

        std::vector<Vector3> vertices;

        std::string line;
        while (std::getline(in, line)) {
            if (line.substr(0,2)=="v ") {
                std::istringstream v(line.substr(2));
                Vector3 vertex;

                float x,y,z;
                v >> x;
                v >> y;
                v >> z;

                vertex.x = x;
                vertex.y = y;
                vertex.z = z;

                vertices.push_back(vertex);
            }
        }

        return vertices;
    }

    static std::vector<MyPolygon> LoadObjModelPolygons(const char *filename) {
        std::ifstream in(filename, std::ios::in);
        if (!in) {
            std::cerr << "Cannot open " << filename << std::endl;
            exit(1);
        }

        std::vector<Vector3> vertices;
        std::vector<MyPolygon> polygons;

        std::string line;
        while (std::getline(in, line)) {
            if (line.substr(0,2)=="v ") {
                std::istringstream v(line.substr(2));
                Vector3 vertex;

                v >> vertex.x;
                v >> vertex.y;
                v >> vertex.z;

                vertices.push_back(vertex);
            }

            if (line.substr(0,2)=="f ")
            {
                std::istringstream v(line.substr(2));

                std::array<Vector3, 3> pVerts;

                int f[3];
                v >> f[0];
                v >> f[1];
                v >> f[2];

                pVerts[0] = vertices[f[0] - 1];
                pVerts[1] = vertices[f[1] - 1];
                pVerts[2] = vertices[f[2] - 1];

                polygons.emplace_back(MyPolygon(pVerts));
            }
        }


        return polygons;
    }
};


#endif //V_3D_OBJECTLOADER_H
