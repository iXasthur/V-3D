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
    static Object LoadObjModel(const std::string &filename) {
        Object obj = Object();
        obj.name = filename;

        std::vector<Vector3> vertices;
        std::vector<MyPolygon> polygons;
        std::vector<Vector3> normals;

        std::ifstream in(filename, std::ios::in);
        if (in) {
            std::string line;
            while (std::getline(in, line)) {
                if (line.substr(0,2) == "v ") {
                    std::istringstream v(line.substr(2));
                    Vector3 vertex;

                    v >> vertex.x;
                    v >> vertex.y;
                    v >> vertex.z;

                    vertices.push_back(vertex);
                } else if (line.substr(0,3) == "vn ") {
                    std::istringstream v(line.substr(3));
                    Vector3 normal;

                    v >> normal.x;
                    v >> normal.y;
                    v >> normal.z;

                    normals.push_back(normal);
                } else if (line.substr(0,2) == "f ") {
                    std::istringstream v(line);

                    int q = 0;

                    std::vector<int> f;
                    std::vector<int> t;
                    std::vector<int> n;

                    while (!v.eof()) {
                        if (v.peek() == ' ') {
                            int fv;
                            v >> fv;
                            f.emplace_back(fv);

                            q = 0;
                            while (v.peek() == '/') {
                                v.ignore();
                                if (v.peek() == '/') {
                                    q++;
                                    v.ignore();
                                }

                                v >> fv;
                                if (q == 0) {
                                    t.emplace_back(fv);
                                    q++;
                                } else if (q == 1) {
                                    n.emplace_back(fv);
                                    q++;
                                }
                            }
                        } else {
                            v.ignore();
                        }
                    }

                    std::array<Vector3, 3> pVertices;
                    std::array<Vector3, 3> pNormals;
                    if (f.size() == 3) {
                        pVertices[0] = vertices[f[0] - 1];
                        pVertices[1] = vertices[f[1] - 1];
                        pVertices[2] = vertices[f[2] - 1];

                        if (!normals.empty()) {
                            pNormals[0] = normals[n[0] - 1];
                            pNormals[1] = normals[n[1] - 1];
                            pNormals[2] = normals[n[2] - 1];
                            polygons.emplace_back(MyPolygon(pVertices, pNormals));
                        } else {
                            polygons.emplace_back(MyPolygon(pVertices));
                        }

                    } else if (f.size() == 4) {
                        pVertices[0] = vertices[f[0] - 1];
                        pVertices[1] = vertices[f[1] - 1];
                        pVertices[2] = vertices[f[2] - 1];

                        if (!normals.empty()) {
                            pNormals[0] = normals[n[0] - 1];
                            pNormals[1] = normals[n[1] - 1];
                            pNormals[2] = normals[n[2] - 1];
                            polygons.emplace_back(MyPolygon(pVertices, pNormals));
                        } else {
                            polygons.emplace_back(MyPolygon(pVertices));
                        }

                        pVertices[0] = vertices[f[0] - 1];
                        pVertices[1] = vertices[f[2] - 1];
                        pVertices[2] = vertices[f[3] - 1];

                        if (!normals.empty()) {
                            pNormals[0] = normals[n[0] - 1];
                            pNormals[1] = normals[n[2] - 1];
                            pNormals[2] = normals[n[3] - 1];
                            polygons.emplace_back(MyPolygon(pVertices, pNormals));
                        } else {
                            polygons.emplace_back(MyPolygon(pVertices));
                        }
                    } else {
                        std::cerr << "Object face must have 3 or 4 vertices" << std::endl;
                    }
                }
            }
        } else {
            std::cerr << "Cannot open " << filename << std::endl;
        }

        obj.polygons = polygons;
        return obj;
    }
};


#endif //V_3D_OBJECTLOADER_H
