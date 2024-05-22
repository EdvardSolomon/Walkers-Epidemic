#include "Game.h"
#include "../core/input/Input.h"
#include "scene/Scene.h"
#include "../engine_backend/EngineBackend.h"

namespace Game {
    GameMode _gameMode = {};
    MultiplayerMode _multiplayerMode = {};
    bool _isLoaded = false;
    double _lastFrame = 0;
    double _thisFrame = 0;
    double _deltaTimeAccumulator = 0.0;
    double _fixedDeltaTime = 1.0 / 60.0;
    bool _showDebugText = false;

    void Create() {
        _gameMode = GameMode::GAME;
        _multiplayerMode = MultiplayerMode::LOCAL;
        _lastFrame = glfwGetTime();
        _thisFrame = _lastFrame;
        _isLoaded = true;

        Scene::LoadMapNEW("map.txt");
    }

    bool IsLoaded() {
        return _isLoaded;
    }

    void Update() {
        _lastFrame = _thisFrame;
        _thisFrame = glfwGetTime();
        double deltaTime = _thisFrame - _lastFrame;
        _deltaTimeAccumulator += deltaTime;

        std::cout << "Current Time: " << _thisFrame << " s, Delta Time: " << deltaTime << " s" << std::endl;

        Scene::Update(deltaTime);
    }

    const bool DebugTextIsEnabled() {
        return _showDebugText;
    }
}
