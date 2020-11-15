//
// Created by iXasthur on 15.11.2020.
//

#ifndef V_3D_ENGINE_H
#define V_3D_ENGINE_H

#include <array>
#include "gl/gl.h"
#include "scene/Scene.h"

class Engine {
public:
    unsigned int fps = 120;
    Scene scene = Scene();

    void createExampleScene() {
        scene = Scene();

        scene.camera.position = {0, 0, 10};

        Object obj = Object();
        std::array<Vector3, 3> vertices;
        vertices[0] = Vector3(1, 1, 0);
        vertices[1] = Vector3(1, -1, 0);
        vertices[2] = Vector3(-1, 1, 0);
        auto polygon = MyPolygon(vertices);
        obj.addPolygon(polygon);

        scene.add(obj);
    }

    void draw(HDC hdc) {
        std::vector<float> vertices = scene.getVertices();

        glClearColor(scene.backgroundColor.Rf, scene.backgroundColor.Gf, scene.backgroundColor.Bf, scene.backgroundColor.Af);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();

        // Move scene
        glTranslatef(-scene.camera.position.x, -scene.camera.position.y, -scene.camera.position.z);

        glEnableClientState(GL_VERTEX_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, vertices.data());
        glColor3f(0.0f, 0.5f, 0.0f);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glDisableClientState(GL_VERTEX_ARRAY);

        glPopMatrix();

        SwapBuffers(hdc);

        Sleep(1000/fps);
    }
};


#endif //V_3D_ENGINE_H
