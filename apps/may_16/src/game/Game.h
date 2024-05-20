namespace Game {
    
    enum class GameMode { GAME, EDITOR_TOP_DOWN, EDITOR_3D };
    enum class MultiplayerMode { NONE, LOCAL, ONLINE };

    void Create();
    bool IsLoaded();
    void Update();
    const bool DebugTextIsEnabled();

}
