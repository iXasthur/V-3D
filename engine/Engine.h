//
// Created by iXasthur on 15.11.2020.
//

#ifndef V_3D_ENGINE_H
#define V_3D_ENGINE_H

#include <array>
#include "gl/gl.h"
#include "scene/Scene.h"
#include "object/ObjectFactory.h"

class Engine {
public:
    int fps = 120;
    const float cameraMoveDelta = 0.1f;
    const float cameraRotationDelta = 1.5f;

    float alphaY = 0;
    Scene scene = Scene();

    void createExampleScene() {
        scene = Scene();

        scene.camera.position = {0, 1, 5};

        scene.add(ObjectFactory::pyramid());
    }

    void handleKeys() {
        if (GetKeyState(0x41) < 0) {
            scene.camera.position.x -= cameraMoveDelta;
        }
        if (GetKeyState(0x44) < 0) {
            scene.camera.position.x += cameraMoveDelta;
        }
        if (GetKeyState(0x57) < 0) {
            scene.camera.position.z -= cameraMoveDelta;
        }
        if (GetKeyState(0x53) < 0) {
            scene.camera.position.z += cameraMoveDelta;
        }
        if (GetKeyState(VK_SHIFT) < 0) {
            scene.camera.position.y -= cameraMoveDelta;
        }
        if (GetKeyState(VK_SPACE) < 0) {
            scene.camera.position.y += cameraMoveDelta;
        }
        if (GetKeyState(VK_LEFT) < 0) {
            scene.camera.eulerRotation.y -= cameraRotationDelta;
        }
        if (GetKeyState(VK_RIGHT) < 0) {
            scene.camera.eulerRotation.y += cameraRotationDelta;
        }
        if (GetKeyState(VK_UP) < 0) {
            scene.camera.eulerRotation.x -= cameraRotationDelta;
        }
        if (GetKeyState(VK_DOWN) < 0) {
            scene.camera.eulerRotation.x += cameraRotationDelta;
        }
    }

    void draw(HDC hdc) {

        glClearColor(scene.backgroundColor.Rf, scene.backgroundColor.Gf, scene.backgroundColor.Bf, scene.backgroundColor.Af);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Push to save perspective projection
        glPushMatrix();

        // Rotate and scene (simulate camera)
        glRotatef(scene.camera.eulerRotation.x, 1, 0, 0);
        glRotatef(scene.camera.eulerRotation.y, 0, 1, 0);
        glRotatef(scene.camera.eulerRotation.y, 0, 0, 0);
        glTranslatef(-scene.camera.position.x, -scene.camera.position.y, -scene.camera.position.z);

        float lightPosition[] = {-10, -20, -10, 0};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        glRotatef(alphaY, 0, 1, 0);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
            for (Object &obj : scene.objects) {
                std::vector<float> vertices = obj.getVertices();
                std::vector<float> normals = obj.getNormals();

                glPushMatrix();

                glTranslatef(obj.position.x, obj.position.y, obj.position.z);
                glColor3f(obj.color.Rf, obj.color.Gf, obj.color.Bf);

                glNormalPointer(GL_FLOAT, 0, normals.data());
                glVertexPointer(3, GL_FLOAT, 0, vertices.data());
                glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

                glPopMatrix();
            }
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);


        glPopMatrix();

        SwapBuffers(hdc);

        alphaY += 180.0f / (float)fps;
    }
};


#endif //V_3D_ENGINE_H
