#pragma once

class Application;

class Controller {
public:
    Controller(Application* app);
    void handleKeyInput(int key, int scancode, int action, int mods);
    void handleMouseInput(double xpos, double ypos);

    void updateCamera();
    void updateLightSource();

private:
    Application* app;

    int mode;
    bool moveCameraForward, moveCameraBackward, moveCameraRight, moveCameraLeft, moveCameraUp, moveCameraDown, mouseChanged,
        moveLightSourceForward, moveLightSourceBackward, moveLightSourceRight, moveLightSourceLeft, moveLightSourceUp, moveLightSourceDown;
    float xOffset, yOffset;
};
