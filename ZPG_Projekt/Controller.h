#pragma once

class Application;

class Controller {
public:
    Controller(Application* app);
    void handleKeyInput(int key, int scancode, int action, int mods);
    void handleMouseInput(double xpos, double ypos);
    void updateCamera();

private:
    Application* app;

    int mode;
    bool moveForward, moveBackward, moveRight, moveLeft, moveUp, moveDown, mouseChanged;
    float xOffset, yOffset;
};
