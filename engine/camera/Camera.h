//
// Created by iXasthur on 14.11.2020.
//

#ifndef V_3D_CAMERA_H
#define V_3D_CAMERA_H

#include "../utils/Vector3.h"
#include "../utils/EulerAngle.h"

class Camera {
public:
    Vector3 position;
    EulerAngle eulerRotation;
};


#endif //V_3D_CAMERA_H
