#include "Cube.h"
#include "../../Util.hpp"

Cube::Cube(glm::vec3 position, float size, int materialIndex) 
    : position(position), size(size), materialIndex(materialIndex) {}

void Cube::CreateVertexData() {
    vertices = {
        // Передняя грань
        Vertex(glm::vec3(-size / 2, -size / 2,  size / 2), glm::vec3(0.0f, 0.0f, 1.0f)),
        Vertex(glm::vec3(size / 2, -size / 2,  size / 2), glm::vec3(0.0f, 0.0f, 1.0f)),
        Vertex(glm::vec3(size / 2,  size / 2,  size / 2), glm::vec3(0.0f, 0.0f, 1.0f)),
        Vertex(glm::vec3(-size / 2,  size / 2,  size / 2), glm::vec3(0.0f, 0.0f, 1.0f)),
        // Задняя грань
        Vertex(glm::vec3(-size / 2, -size / 2, -size / 2), glm::vec3(0.0f, 0.0f, -1.0f)),
        Vertex(glm::vec3(size / 2, -size / 2, -size / 2), glm::vec3(0.0f, 0.0f, -1.0f)),
        Vertex(glm::vec3(size / 2,  size / 2, -size / 2), glm::vec3(0.0f, 0.0f, -1.0f)),
        Vertex(glm::vec3(-size / 2,  size / 2, -size / 2), glm::vec3(0.0f, 0.0f, -1.0f)),
        // Верхняя грань
        Vertex(glm::vec3(-size / 2,  size / 2, -size / 2), glm::vec3(0.0f, 1.0f, 0.0f)),
        Vertex(glm::vec3(size / 2,  size / 2, -size / 2), glm::vec3(0.0f, 1.0f, 0.0f)),
        Vertex(glm::vec3(size / 2,  size / 2,  size / 2), glm::vec3(0.0f, 1.0f, 0.0f)),
        Vertex(glm::vec3(-size / 2,  size / 2,  size / 2), glm::vec3(0.0f, 1.0f, 0.0f)),
        // Нижняя грань
        Vertex(glm::vec3(-size / 2, -size / 2, -size / 2), glm::vec3(0.0f, -1.0f, 0.0f)),
        Vertex(glm::vec3(size / 2, -size / 2, -size / 2), glm::vec3(0.0f, -1.0f, 0.0f)),
        Vertex(glm::vec3(size / 2, -size / 2,  size / 2), glm::vec3(0.0f, -1.0f, 0.0f)),
        Vertex(glm::vec3(-size / 2, -size / 2,  size / 2), glm::vec3(0.0f, -1.0f, 0.0f)),
        // Левая грань
        Vertex(glm::vec3(-size / 2, -size / 2, -size / 2), glm::vec3(-1.0f, 0.0f, 0.0f)),
        Vertex(glm::vec3(-size / 2, -size / 2,  size / 2), glm::vec3(-1.0f, 0.0f, 0.0f)),
        Vertex(glm::vec3(-size / 2,  size / 2,  size / 2), glm::vec3(-1.0f, 0.0f, 0.0f)),
        Vertex(glm::vec3(-size / 2,  size / 2, -size / 2), glm::vec3(-1.0f, 0.0f, 0.0f)),
        // Правая грань
        Vertex(glm::vec3(size / 2, -size / 2, -size / 2), glm::vec3(1.0f, 0.0f, 0.0f)),
        Vertex(glm::vec3(size / 2, -size / 2,  size / 2), glm::vec3(1.0f, 0.0f, 0.0f)),
        Vertex(glm::vec3(size / 2,  size / 2,  size / 2), glm::vec3(1.0f, 0.0f, 0.0f)),
        Vertex(glm::vec3(size / 2,  size / 2, -size / 2), glm::vec3(1.0f, 0.0f, 0.0f))
    };

    indices = {
        // Передняя грань
        0, 1, 2, 2, 3, 0,
        // Задняя грань
        4, 5, 6, 6, 7, 4,
        // Верхняя грань
        8, 9, 10, 10, 11, 8,
        // Нижняя грань
        12, 13, 14, 14, 15, 12,
        // Левая грань
        16, 17, 18, 18, 19, 16,
        // Правая грань
        20, 21, 22, 22, 23, 20
    };
}

void Cube::CreateMeshGL() {
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Cube::Draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Cube::CleanUp() {
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        VAO = VBO = EBO = 0;
    }
}

bool Cube::PointIsInsideCube(glm::vec3 point) {
    glm::vec3 halfSize = glm::vec3(size / 2.0f);
    glm::vec3 min = position - halfSize;
    glm::vec3 max = position + halfSize;
    return (point.x >= min.x && point.x <= max.x &&
            point.y >= min.y && point.y <= max.y &&
            point.z >= min.z && point.z <= max.z);
}
