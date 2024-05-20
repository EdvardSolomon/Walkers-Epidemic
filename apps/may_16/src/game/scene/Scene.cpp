#include "Scene.h"
#include "../../engine_backend/EngineBackend.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Scene {
    void Update(float deltaTime) {
        // Здесь можно обновить состояние сцены, если это необходимо.
    }

    void LoadMapNEW(std::string mapPath) {
        CleanUp();

        // // Компиляция вершинного шейдера
        // unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        // glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        // glCompileShader(vertexShader);
        // checkShaderCompilation(vertexShader);

        // // Компиляция фрагментного шейдера
        // unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        // glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        // glCompileShader(fragmentShader);
        // checkShaderCompilation(fragmentShader);

        // // Линковка шейдерной программы
        // shaderProgram = glCreateProgram();
        // glAttachShader(shaderProgram, vertexShader);
        // glAttachShader(shaderProgram, fragmentShader);
        // glLinkProgram(shaderProgram);
        // checkProgramLinking(shaderProgram);
        // glDeleteShader(vertexShader);
        // glDeleteShader(fragmentShader);

    // Хардкодим создание кубов
        int numberOfCubes = 10;  // пример количества кубов
        for (int i = 0; i < numberOfCubes; ++i) {
            glm::vec3 position = glm::vec3(i * 2.0f, 0.0f, 0.0f);  // просто пример позиции
            Cube cube(position, 1.0f, 0);
            cube.CreateVertexData();
            cube.CreateMeshGL();
            _cubes.push_back(cube);
            
        }

    // // OpenGL буферы инициализация
    // glGenVertexArrays(1, &floorVAO);
    // glGenBuffers(1, &floorVBO);
    // glGenBuffers(1, &floorEBO);

    // glBindVertexArray(floorVAO);

    // glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
    // glBufferData(GL_ARRAY_BUFFER, cubeVertices.size() * sizeof(float), cubeVertices.data(), GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, floorEBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, floorIndices.size() * sizeof(unsigned int), floorIndices.data(), GL_STATIC_DRAW);

    // // Указатели вершинных атрибутов
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
    }

    void CleanUp() {
        _cubes.clear();
    }

    void RecreateDataStructures() {
        CreateMeshData();
    }

    void CreateMeshData() {
        // Здесь можно создать данные меша, если это необходимо
    }
}
