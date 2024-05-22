# file(GLOB SRCS
# "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*"
# )

# Engine backend files
set(ENGINE_BACKEND_SRCS
    src/engine_backend/EngineBackend.cpp
    src/engine_backend/GL_EngineBackend.cpp
    src/engine_backend/GL_Renderer.cpp
    src/engine_backend/types/GL_shader.cpp
)

# Renderer files
set(RENDERER_SRCS
    src/renderer/Renderer.cpp
    src/renderer/TextBlitting.cpp
)

# Input files
set(INPUT_SRCS
    src/core/input/Input.cpp
)

# Types files
set(TYPES_SRCS

    # src/types/DetachedMesh.hpp
    # src/types/GL_detachedMesh.hpp
    src/types/modular/Cube.cpp
)

# Engine files
set(ENGINE_SRCS
    src/Engine.cpp
)

# Game files
set(GAME_SRCS
    src/game/Game.cpp
)

# Scene files
set(SCENE_SRCS
    src/game/scene/Scene.cpp
)

# Main file
set(MAIN_SRCS
    src/Main.cpp
)

# Combine all source files
set(SRCS
    ${ENGINE_SRCS}
    ${ENGINE_BACKEND_SRCS}
    ${GAME_SRCS}
    ${TYPES_SRCS}
    ${SCENE_SRCS}
    ${RENDERER_SRCS}
    ${INPUT_SRCS}
    ${MAIN_SRCS}
)

message(STATUS "SRCS = ${SRCS}")

# message(STATUS "GLFW_LIBRARY = ${GLFW_LIBRARY}")
add_executable(may_16 ${SRCS})
target_link_libraries(may_16 ${GLAD_LIBRARY} ${GLFW_LIBRARY} ${IMGUI_LIBRARY} ${ASSIMP_LIBRARY})

# Resources
set(SOURCE_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/res)
set(TARGET_RESOURCES_DIR ${CMAKE_CURRENT_BINARY_DIR}/res)

add_custom_command(
    TARGET may_16 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SOURCE_RESOURCES_DIR} ${TARGET_RESOURCES_DIR}
)
