#pragma once

class Application;

class Controller {
public:
    Controller(Application* app);
    void handleKeyInput(int key, int scancode, int action, int mods);
    void handleWindowResize(int width, int height);
    void handleMouseInput(double xpos, double ypos);
    void handleMouseClickInput(int button, int action, int mode);

    void updateCamera();

private:
    Application* app;

    int mode, windowHeight, windowWidth;
    bool moveCameraForward, moveCameraBackward, moveCameraRight, moveCameraLeft, moveCameraUp, moveCameraDown, mouseChanged,
        windowSizeChanged, cursorLocked;
    float xOffset, yOffset;
};
