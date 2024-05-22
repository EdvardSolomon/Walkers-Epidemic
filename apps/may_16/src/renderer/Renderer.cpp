#include "Renderer.h"
#include <vector>
#include <string>
#include "../game/scene/Scene.h"
#include "../engine_backend/GL_Renderer.h"
#include "../engine_backend/EngineBackend.h"
#include "../renderer/TextBlitter.h"
#include "../renderer/RenderData.h"



std::vector<RenderItem2D> CreateLoadingScreenRenderItems();
std::vector<RenderItem2D> CreateRenderItems2D();
std::vector<RenderItem3D> CreateRenderItems3D();
CameraData CreateCameraData();
RenderData CreateRenderData();
void RenderGame(RenderData& renderData);

void Renderer::RenderFrame() {
    // Create render data
    RenderData renderData = CreateRenderData();
    
    // Perform rendering
    RenderGame(renderData);
    
    // Present the final image
    glfwSwapBuffers(EngineBackend::GetWindowPointer());
}

std::vector<RenderItem2D> CreateLoadingScreenRenderItems() {
    // Example loading screen render items
    std::string text = "Loading...";
    ivec2 location = ivec2(50, 50);
    ivec2 viewportSize = ivec2(800, 600);  // Example size
    return TextBlitter::CreateText(text, location, viewportSize, Alignment::TOP_LEFT, BitmapFontType::STANDARD);
}

std::vector<RenderItem2D> CreateRenderItems2D() {
    // Example 2D render items
    std::string text = "Example HUD";
    ivec2 location = ivec2(10, 10);
    ivec2 viewportSize = ivec2(800, 600);  // Example size
    return TextBlitter::CreateText(text, location, viewportSize, Alignment::TOP_LEFT, BitmapFontType::STANDARD);
}

std::vector<RenderItem3D> CreateRenderItems3D() {
    // Example 3D render items
    std::vector<RenderItem3D> renderItems = Scene::GetAllRenderItems();
    return renderItems;
}

CameraData CreateCameraData() {
    CameraData cameraData;
    // Set example camera matrices
    cameraData.projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    cameraData.view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    cameraData.projectionInverse = glm::inverse(cameraData.projection);
    cameraData.viewInverse = glm::inverse(cameraData.view);
    cameraData.viewportWidth = 800;  // Example size
    cameraData.viewportHeight = 600; // Example size
    return cameraData;
}

RenderData CreateRenderData() {
    RenderData renderData;
    renderData.lights = std::vector<GPULight>(); // Example empty lights
    renderData.renderDebugLines = false; // Example: no debug lines
    renderData.playerIndex = 0; // Example: single player
    renderData.cameraData = CreateCameraData();
    
    std::vector<RenderItem3D> geometryRenderItems = CreateRenderItems3D();

    renderData.renderItems2D = CreateRenderItems2D();
    renderData.renderItems2DHiRes = std::vector<RenderItem2D>(); // Example: no hi-res items
    renderData.blitDstCoords = BlitDstCoords{0, 0, 800, 600}; // Example size
    renderData.blitDstCoordsPresent = BlitDstCoords{0, 0, 800, 600}; // Example size
    renderData.animatedRenderItems3D = std::vector<RenderItem3D>(); // Example: no animated items
    renderData.animatedTransforms = nullptr; // Example: no animated transforms
    renderData.finalImageColorTint = glm::vec3(1.0f); // Example tint
    renderData.finalImageColorContrast = 1.0f; // Example contrast
    renderData.renderMode = RenderMode::COMPOSITE; // Example render mode
    renderData.geometryDrawInfo = MultiDrawIndirectDrawInfo(); // Example draw info
    renderData.shadowMapGeometryDrawInfo = MultiDrawIndirectDrawInfo(); // Example draw info

    return renderData;
}

void RenderGame(RenderData& renderData) {
    OpenGLRenderer::RenderGame(renderData);
}

void Renderer::RenderLoadingScreen() {
    std::vector<RenderItem2D> renderItems = CreateLoadingScreenRenderItems();
}

void ResizeRenderTargets() {

    int width = PRESENT_WIDTH;
    int height = PRESENT_HEIGHT;

    // OpenGLRenderer::CreatePlayerRenderTargets(width, height);
}

void Renderer::HotloadShaders() {}
