//
// Created by iXasthur on 15.11.2020.
//

#ifndef V_3D_ENGINE_H
#define V_3D_ENGINE_H

#include <array>
#include "gl/gl.h"
#include "scene/Scene.h"
#include <cmath>

class Engine {
public:
    enum class RenderMode {
        SOLID,
        WIREFRAME
    };

    const int fps = 120;
    const float cameraMoveDeltaAbsolute = 1.0f;
    const float cameraRotationDelta = 1.5f;
    RenderMode renderMode = RenderMode::SOLID;

    Scene scene = Scene();

    Engine() = default;

    void handleKeys() {
        float moveSpeed = 0;
        if (GetKeyState(0x57) < 0) { // W
            moveSpeed = cameraMoveDeltaAbsolute;
        }
        if (GetKeyState(0x53) < 0) { // S
            moveSpeed = -cameraMoveDeltaAbsolute;
        }
        if (moveSpeed != 0) {
            float alphaY = scene.camera.eulerRotation.y;
            scene.camera.position.x -= sin(-alphaY / 180.0f * M_PI) * moveSpeed;
            scene.camera.position.z -= cos(-alphaY / 180.0f * M_PI) * moveSpeed;
        }

        moveSpeed = 0;
        if (GetKeyState(0x44) < 0) { // D
            moveSpeed = cameraMoveDeltaAbsolute;
        }
        if (GetKeyState(0x41) < 0) { // A
            moveSpeed = -cameraMoveDeltaAbsolute;
        }
        if (moveSpeed != 0) {
            float alphaY = scene.camera.eulerRotation.y;
            scene.camera.position.x += cos(-alphaY / 180.0f * M_PI) * moveSpeed;
            scene.camera.position.z -= sin(-alphaY / 180.0f * M_PI) * moveSpeed;
        }

        if (GetKeyState(VK_SHIFT) < 0) {
            scene.camera.position.y -= cameraMoveDeltaAbsolute;
        }
        if (GetKeyState(VK_SPACE) < 0) {
            scene.camera.position.y += cameraMoveDeltaAbsolute;
        }

        if (GetKeyState(VK_LEFT) < 0) {
            scene.camera.eulerRotation.y -= cameraRotationDelta;
        }
        if (GetKeyState(VK_RIGHT) < 0) {
            scene.camera.eulerRotation.y += cameraRotationDelta;
        }
        if (GetKeyState(VK_UP) < 0) {
            if (scene.camera.eulerRotation.x > -90.0f) {
                scene.camera.eulerRotation.x -= cameraRotationDelta;
            } else {
                scene.camera.eulerRotation.x = -90.0f;
            }
        }
        if (GetKeyState(VK_DOWN) < 0) {
            if (scene.camera.eulerRotation.x < 90.0f) {
                scene.camera.eulerRotation.x += cameraRotationDelta;
            } else {
                scene.camera.eulerRotation.x = 90.0f;
            }
        }
    }

    void draw(HDC hdc) {
        switch (renderMode) {
            case RenderMode::SOLID:
                glPolygonMode(GL_FRONT, GL_FILL);
                glPolygonMode(GL_BACK, GL_FILL);
                break;
            case RenderMode::WIREFRAME:
                glPolygonMode(GL_FRONT, GL_LINE);
                glPolygonMode(GL_BACK, GL_LINE);
                break;
        }

        // Clear screen
        glClearColor(scene.backgroundColor.Rf, scene.backgroundColor.Gf, scene.backgroundColor.Bf,
                     scene.backgroundColor.Af);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Push to save perspective projection
        glPushMatrix();

        // Rotate and scene (simulate camera)
        glRotatef(scene.camera.eulerRotation.x, 1, 0, 0);
        glRotatef(scene.camera.eulerRotation.y, 0, 1, 0);
        glRotatef(scene.camera.eulerRotation.z, 0, 0, 1);
        glTranslatef(-scene.camera.position.x, -scene.camera.position.y, -scene.camera.position.z);

        // Set light
        glLightfv(GL_LIGHT0, GL_POSITION, scene.light.position.toArray().data());

        // Rotate scene
        glRotatef(scene.eulerRotation.x, 1, 0, 0);
        glRotatef(scene.eulerRotation.y, 0, 1, 0);
        glRotatef(scene.eulerRotation.z, 0, 0, 1);

        // Draw
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
    }

    std::string description() {
        std::string s;
        for (const Object &obj : scene.objects) {
            s += obj.name + ", ";
        }
        s += scene.camera.position.toString();
        s += ", light: " + std::to_string(scene.light.currentLightPositionIndex);
        switch (renderMode) {
            case RenderMode::SOLID:
                s += ", SOLID";
                break;
            case Engine::RenderMode::WIREFRAME:
                s += ", WIREFRAME";
                break;
        }
        return s;
    }
};


#endif //V_3D_ENGINE_H
