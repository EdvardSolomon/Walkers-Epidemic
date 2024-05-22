#pragma once

#include <glm/glm.hpp>
#include "../../Util.hpp"
#include "../../renderer/RendererCommon.h"

class Cube {
public:
    Cube(glm::vec3 position, float size, int materialIndex);
    void CreateVertexData();
    void CreateMeshGL();
    void Draw();
    void CleanUp();
    bool PointIsInsideCube(glm::vec3 point);
    glm::vec3 getPosition() const { return position; }
    RenderItem3D GetRenderItem();

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO = 0, VBO = 0, EBO = 0;
    glm::vec3 position;
    float size;
    int materialIndex;
    RenderItem3D renderItem;
};
