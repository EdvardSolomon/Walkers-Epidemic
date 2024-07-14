cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

project(OpenGL_apps)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -static -static-libgcc -static-libstdc++")

add_definitions(-DUNICODE -D_UNICODE)

set(BABYMA_DLL ${CMAKE_SOURCE_DIR}/build/apps/babyma/libbabymad.dll)

set(GLFW_LIBRARY ${CMAKE_SOURCE_DIR}/third_party/glfw/build/src/libglfw3.a)
set(GLAD_LIBRARY ${CMAKE_SOURCE_DIR}/third_party/glad/build/libglad.a)
set(IMGUI_LIBRARY ${CMAKE_SOURCE_DIR}/third_party/imgui/build/libimgui.a)
set(ASSIMP_LIBRARY ${CMAKE_SOURCE_DIR}/third_party/assimp/build/lib/libassimpd.a)

include_directories(${CMAKE_SOURCE_DIR}/third_party/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/stb)
include_directories(${CMAKE_SOURCE_DIR}/third_party/glm)
include_directories(${CMAKE_SOURCE_DIR}/third_party/glew-2.1.0/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/imgui/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/tiny_obj_loader)
include_directories(${CMAKE_SOURCE_DIR}/third_party/assimp/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/assimp/build/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/rapidjson/include)

add_subdirectory(apps)
