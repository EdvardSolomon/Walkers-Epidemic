#include "EngineBackend.h"
#include <iostream>
#include <string>
#include "../core/input/Input.h"

namespace EngineBackend {
    GLFWwindow* _window = NULL;
    WindowedMode _windowedMode = WindowedMode::WINDOWED;
    GLFWmonitor* _monitor;
    const GLFWvidmode* _mode;
    bool _forceCloseWindow = false;
    bool _windowHasFocus = true;
    int _windowedWidth = 0;
    int _windowedHeight = 0;
    int _fullscreenWidth = 0;
    int _fullscreenHeight = 0;
    int _currentWindowWidth = 0;
    int _currentWindowHeight = 0;
    int _presentTargetWidth = 0;
    int _presentTargetHeight = 0;

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void window_focus_callback(GLFWwindow* window, int focused);


    void Init() {

        int width = 1920 * 1.5f;
        int height = 1080 * 1.5f;

        glfwInit();
        // What is this?
        glfwSetErrorCallback([](int error, const char* description) { std::cout << "GLFW Error (" << std::to_string(error) << "): " << description << "\n";});

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);

        // Resolution and window size
        _monitor = glfwGetPrimaryMonitor();
        _mode = glfwGetVideoMode(_monitor);
        glfwWindowHint(GLFW_RED_BITS, _mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, _mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, _mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, _mode->refreshRate);
        _fullscreenWidth = _mode->width;
        _fullscreenHeight = _mode->height;
        _windowedWidth = width;
        _windowedHeight = height;
        CreateGLFWWindow(WindowedMode::WINDOWED);
        if (_window == NULL) {
            std::cout << "Failed to create GLFW window\n";
            glfwTerminate();
            return;
        }
        glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
        glfwSetWindowFocusCallback(_window, window_focus_callback);

        // AssetManager::FindAssetPaths();
        
        glfwMakeContextCurrent(_window);
        // OpenGLBackEnd::InitMinimum();
        // OpenGLRenderer::InitMinimum();
        // Renderer_OLD::InitMinimumGL(); 
        // glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD\n";
            return;
        }

        // OpenGL initial setup
        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* renderer = glGetString(GL_RENDERER);
        std::cout << "\nGPU: " << renderer << "\n";
        std::cout << "GL version: " << major << "." << minor << "\n\n";

        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // AssetManager::LoadFont();

        // Init sub-systems
        Input::Init();
        // Audio::Init();
        // Physics::Init();
        // InputMulti::Init();
        glfwShowWindow(EngineBackend::GetWindowPointer());
    }

    void BeginFrame() {
        glfwPollEvents();
    }

    void EndFrame() {
        glfwSwapBuffers(_window);
    }

    void UpdateSubSystems() {
        Input::Update();
        // Audio::Update();
    }

    void CleanUp() {
        glfwTerminate();
    }

    // Window
    GLFWwindow* GetWindowPointer() {
        return _window;
    }

    void SetWindowPointer(GLFWwindow* window) {
        _window = window;
    }

    void CreateGLFWWindow(const WindowedMode& windowedMode) {
        if (windowedMode == WindowedMode::WINDOWED) {
            _currentWindowWidth = _windowedWidth;
            _currentWindowHeight = _windowedHeight; 
            _window = glfwCreateWindow(_windowedWidth, _windowedHeight, "Unloved", NULL, NULL);
            glfwSetWindowPos(_window, 0, 0);
        }
        else if (windowedMode == WindowedMode::FULLSCREEN) {
            _currentWindowWidth = _fullscreenWidth;
            _currentWindowHeight = _fullscreenHeight;
            _window = glfwCreateWindow(_fullscreenWidth, _fullscreenHeight, "Unloved", _monitor, NULL);
        }
        _windowedMode = windowedMode;
    }

    void SetWindowedMode(const WindowedMode& windowedMode) {
        if (windowedMode == WindowedMode::WINDOWED) {
            _currentWindowWidth = _windowedWidth;
            _currentWindowHeight = _windowedHeight;
            glfwSetWindowMonitor(_window, nullptr, 0, 0, _windowedWidth, _windowedHeight, _mode->refreshRate);
            glfwSetWindowPos(_window, 0, 0);
        }
        else if (windowedMode == WindowedMode::FULLSCREEN) {
            _currentWindowWidth = _fullscreenWidth;
            _currentWindowHeight = _fullscreenHeight;
            glfwSetWindowMonitor(_window, _monitor, 0, 0, _fullscreenWidth, _fullscreenHeight, _mode->refreshRate);
        }
        _windowedMode = windowedMode;
    }

    void ToggleFullscreen() {
        if (_windowedMode == WindowedMode::WINDOWED) {
            SetWindowedMode(WindowedMode::FULLSCREEN);
        }
        else {
            SetWindowedMode(WindowedMode::WINDOWED);
        }
    }

    void ForceCloseWindow() {
        _forceCloseWindow = true;
    }

    bool WindowHasFocus() {
        return _windowHasFocus;
    }

    bool WindowHasNotBeenForceClosed() {
        return !_forceCloseWindow;
    }

    int GetWindowedWidth() {
        return _windowedWidth;
    }

    int GetWindowedHeight() {
        return _windowedHeight;
    }

    int GetFullScreenWidth() {
        return _fullscreenWidth;
    }

    int GetFullScreenHeight() {
        return _fullscreenHeight;
    }

    int GetCurrentWindowWidth() {
        return _currentWindowWidth;
    }

    int GetCurrentWindowHeight() {
        return _currentWindowHeight;
    }

    bool WindowIsOpen() {
        return !(glfwWindowShouldClose(_window) || _forceCloseWindow);
    }

    bool WindowIsMinimized() {
        int width = 0;
        int height = 0;
        glfwGetFramebufferSize(_window, &width, &height);
        return (width == 0 || height == 0);
    }

    const WindowedMode& GetWindowMode() {
        return _windowedMode;
    }


    //  Render Targets
    void SetPresentTargetSize(int width, int height) {
        _presentTargetWidth = width;
        _presentTargetHeight = height;

        //OpenGLBackEnd::SetPresentTargetSize(width, height);
    }

    int GetPresentTargetWidth() {
        return _presentTargetWidth;
    }

    int GetPresentTargetHeight() {
        return _presentTargetHeight;
    }


    // Callbacks
    void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void window_focus_callback(GLFWwindow* /*window*/, int focused) {
        if (focused) {
            EngineBackend::_windowHasFocus = true;
        }
        else {
            EngineBackend::_windowHasFocus = false;
        }
    }
}
