//
// Created by iXasthur on 14.11.2020.
//

#ifndef V_3D_CAMERA_H
#define V_3D_CAMERA_H

#include "../utils/Vector3.h"

class Camera {
public:
    static const int zNear = 5;
    static const int zFar = 100;

    Vector3 position;
};


#endif //V_3D_CAMERA_H
