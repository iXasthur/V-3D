cmake_minimum_required(VERSION 3.17)
project(V_3D)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -municode")
set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lOpengl32")

add_executable(V_3D main.cpp engine/scene/Scene.h engine/object/Object.h engine/camera/Camera.h engine/utils/MyPolygon.h engine/utils/Vector3.h engine/utils/Vector4.h engine/Engine.h engine/utils/Color.h engine/utils/EulerAngle.h engine/object/ObjectLoader.h engine/light/Light.h)