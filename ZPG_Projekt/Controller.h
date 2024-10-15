#pragma once

class Application;

class Controller {
public:
    Controller(Application* app);
    void handleKeyInput(int key, int scancode, int action, int mods);
    void handleMouseInput(double xpos, double ypos);

private:
    Application* app;
};
