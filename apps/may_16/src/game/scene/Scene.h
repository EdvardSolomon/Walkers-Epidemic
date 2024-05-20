#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../../renderer/RendererCommon.h"

#include "../../types/modular/Cube.h"

namespace Scene {
    inline std::vector<Cube> _cubes;

    void Update(float deltaTime);
    void LoadMapNEW(std::string mapPath);
    std::vector<RenderItem3D> GetAllRenderItems();
    void CleanUp();
    void RecreateDataStructures();
    void CreateMeshData();
    void Render();
    void SetupFloor();
}

#endif // SCENE_H
