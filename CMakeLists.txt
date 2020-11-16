cmake_minimum_required(VERSION 3.17)
project(V_3D)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -municode")
set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lOpengl32")

add_executable(V_3D main.cpp engine/scene/Scene.cpp engine/scene/Scene.h engine/object/Object.cpp engine/object/Object.h engine/camera/Camera.cpp engine/camera/Camera.h engine/utils/MyPolygon.cpp engine/utils/MyPolygon.h engine/utils/Vector3.cpp engine/utils/Vector3.h engine/utils/Vector4.cpp engine/utils/Vector4.h engine/Engine.cpp engine/Engine.h engine/utils/Color.cpp engine/utils/Color.h engine/object/ObjectFactory.cpp engine/object/ObjectFactory.h engine/utils/EulerAngle.cpp engine/utils/EulerAngle.h engine/object/ObjectLoader.cpp engine/object/ObjectLoader.h engine/light/Light.cpp engine/light/Light.h)