#include "Engine.h"
#include "game/Game.h"
#include "engine_backend/EngineBackend.h"
#include "renderer/Renderer.h"

void Engine::Run() {
    EngineBackend::Init();

    while (EngineBackend::WindowIsOpen()) {

        EngineBackend::BeginFrame();
        EngineBackend::UpdateSubSystems();
        
        if (!Game::IsLoaded()) {
            Game::Create();
        } else {
            Game::Update();
            Renderer::RenderFrame();
        }

        EngineBackend::EndFrame();
    }

    EngineBackend::CleanUp();
}
