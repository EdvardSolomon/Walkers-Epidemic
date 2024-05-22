#include "GL_Renderer.h"
// #include "GL_assetManager.h"
#include "GL_EngineBackend.h"
// #include "Types/GL_gBuffer.h"
#include "types/GL_shader.h"
// #include "Types/GL_shadowMap.h"
#include "types/GL_frameBuffer.hpp"
#include "EngineBackend.h"
#include "../renderer/RendererCommon.h"
#include "../renderer/TextBlitter.h"
#include "../game/scene/Scene.h"
// #include "../Core/AssetManager.h"
#include "../game/Game.h"

namespace OpenGLRenderer {

    struct FrameBuffers {
        GLFrameBuffer present;
    } _frameBuffers;

    struct Shaders {
        Shader basic;
    } _shaders;

    struct SSBOs {
        GLuint cameraData = 0;
        GLuint geometryRenderItems = 0;
    } _ssbos;
}


void DrawRenderItem(RenderItem3D& renderItem);


void MultiDrawIndirect(std::vector<DrawIndexedIndirectCommand>& commands, GLuint vertexArray);

void MultiDrawIndirect(std::vector<RenderItem3D>& renderItems, GLuint vertexArray);
void BlitFrameBuffer(GLFrameBuffer* src, GLFrameBuffer* dst, const char* srcName, const char* dstName, GLbitfield mask, GLenum filter);


void BlitPlayerPresentTargetToDefaultFrameBuffer(GLFrameBuffer* src, GLFrameBuffer* dst, const char* srcName, const char* dstName, GLbitfield mask, GLenum filter, BlitDstCoords& blitDstCoords);

void ClearRenderTargets();
void LightingPass(RenderData& renderData);
void GeometryPass(RenderData& renderData); 
void UploadSSBOsGPU(RenderData& renderData);

void OpenGLRenderer::HotloadShaders() {
    std::cout << "Hotloading shaders...\n";
    _shaders.basic.Load("../../res/shaders/vertex_shader.vert", "fragment_shader.frag");
}

void OpenGLRenderer::CreatePlayerRenderTargets(int presentWidth, int presentHeight) {
    if (_frameBuffers.present.GetHandle() != 0) {
        _frameBuffers.present.CleanUp();
    }

    _frameBuffers.present.Create("Present", presentWidth, presentHeight);
    _frameBuffers.present.CreateAttachment("Color", GL_RGBA8);

    std::cout << "Resizing render targets: " << presentWidth << " x " << presentHeight << "\n";
}

void OpenGLRenderer::InitMinimum() {

    HotloadShaders();
    CreatePlayerRenderTargets(PRESENT_WIDTH, PRESENT_HEIGHT);

  // Shader storage buffer objects
    glGenBuffers(1, &_ssbos.geometryRenderItems);
    glBindBuffer(GL_UNIFORM_BUFFER, _ssbos.geometryRenderItems);
    glBufferData(GL_UNIFORM_BUFFER, MAX_RENDER_OBJECTS_3D * sizeof(RenderItem3D), NULL, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_ssbos.cameraData);
    glBindBuffer(GL_UNIFORM_BUFFER, _ssbos.cameraData);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraData), NULL, GL_DYNAMIC_DRAW);
    // glGenBuffers(1, &_ssbos.geometryRenderItems);
    // glNamedBufferStorage(_ssbos.geometryRenderItems, MAX_RENDER_OBJECTS_3D * sizeof(RenderItem3D), NULL, GL_DYNAMIC_STORAGE_BIT);

    // glGenBuffers(1, &_ssbos.cameraData);
    // glNamedBufferStorage(_ssbos.cameraData, sizeof(CameraData), NULL, GL_DYNAMIC_STORAGE_BIT);
}

/*
   ▄████████    ▄████████ ███▄▄▄▄   ████████▄     ▄████████    ▄████████         ▄███████▄    ▄████████    ▄████████    ▄████████    ▄████████    ▄████████
  ███    ███   ███    ███ ███▀▀▀██▄ ███   ▀███   ███    ███   ███    ███        ███    ███   ███    ███   ███    ███   ███    ███   ███    ███   ███    ███
  ███    ███   ███    █▀  ███   ███ ███    ███   ███    █▀    ███    ███        ███    ███   ███    ███   ███    █▀    ███    █▀    ███    █▀    ███    █▀
 ▄███▄▄▄▄██▀  ▄███▄▄▄     ███   ███ ███    ███  ▄███▄▄▄      ▄███▄▄▄▄██▀        ███    ███   ███    ███   ███          ███         ▄███▄▄▄       ███
▀▀███▀▀▀▀▀   ▀▀███▀▀▀     ███   ███ ███    ███ ▀▀███▀▀▀     ▀▀███▀▀▀▀▀        ▀█████████▀  ▀███████████ ▀███████████ ▀███████████ ▀▀███▀▀▀     ▀███████████
▀███████████   ███    █▄  ███   ███ ███    ███   ███    █▄  ▀███████████        ███          ███    ███          ███          ███   ███    █▄           ███
  ███    ███   ███    ███ ███   ███ ███   ▄███   ███    ███   ███    ███        ███          ███    ███    ▄█    ███    ▄█    ███   ███    ███    ▄█    ███
  ███    ███   ██████████  ▀█   █▀  ████████▀    ██████████   ███    ███       ▄████▀        ███    █▀   ▄████████▀   ▄████████▀    ██████████  ▄████████▀
  ███    ███                                                  ███    ███                                                                                     */


void UploadSSBOsGPU(RenderData& renderData) {
    // Обновляем данные геометрии
    // glNamedBufferSubData(OpenGLRenderer::_ssbos.geometryRenderItems, 0, renderData.geometryDrawInfo.renderItems.size() * sizeof(RenderItem3D), &renderData.geometryDrawInfo.renderItems[0]);
    // glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, OpenGLRenderer::_ssbos.geometryRenderItems);

    // Обновляем данные камеры
    // glNamedBufferSubData(OpenGLRenderer::_ssbos.cameraData, 0, sizeof(CameraData), &renderData.cameraData);
    // glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, OpenGLRenderer::_ssbos.cameraData);
}

void OpenGLRenderer::RenderGame(RenderData& renderData) {

    // GLFrameBuffer& gBuffer = _frameBuffers.gBuffer;
    GLFrameBuffer& present = _frameBuffers.present;

    UploadSSBOsGPU(renderData);
    ClearRenderTargets();

    GeometryPass(renderData);

    // BlitPlayerPresentTargetToDefaultFrameBuffer(&_frameBuffers.present, 0, "Color", "", GL_COLOR_BUFFER_BIT, GL_NEAREST, renderData.blitDstCoords);
}


void ClearRenderTargets() {

    // Clear GBuffer color attachments
    // GLFrameBuffer& gBuffer = OpenGLRenderer::_frameBuffers.gBuffer;
    GLFrameBuffer& present = OpenGLRenderer::_frameBuffers.present;

    // gBuffer.Bind();
    // gBuffer.SetViewport();
    unsigned int attachments[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, attachments);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

/*

 █▀▀█ █▀▀ █▀▀█ █▀▄▀█ █▀▀ ▀▀█▀▀ █▀▀█ █  █ 　 █▀▀█ █▀▀█ █▀▀ █▀▀
 █ ▄▄ █▀▀ █  █ █ ▀ █ █▀▀   █   █▄▄▀ ▀▀▀█ 　 █▄▄█ █▄▄█ ▀▀█ ▀▀█
 █▄▄█ ▀▀▀ ▀▀▀▀ ▀   ▀ ▀▀▀   ▀   ▀ ▀▀ ▀▀▀▀ 　 ▀    ▀  ▀ ▀▀▀ ▀▀▀  */

void GeometryPass(RenderData& renderData) {

    GLFrameBuffer& gBuffer = OpenGLRenderer::_frameBuffers.present;

    // Render target
    gBuffer.Bind();
    gBuffer.SetViewport();
    unsigned int attachments[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, attachments);

    // GL state
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Draw mesh
    Shader& basicShader = OpenGLRenderer::_shaders.basic;
    basicShader.Use();
    basicShader.SetMat4("projection", renderData.cameraData.projection);
    basicShader.SetMat4("view", renderData.cameraData.view);
    // MultiDrawIndirect(renderData.geometryDrawInfo.commands, OpenGLBackEnd::GetVertexDataVAO());
}

