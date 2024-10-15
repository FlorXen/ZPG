#include "Controller.h"
#include "Application.h"

Controller::Controller(Application* app) : app(app) {}

void Controller::handleKeyInput(int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_W && action != GLFW_RELEASE) {
        app->moveCamera('f', (mods == 1)?0.3:0.1);
    }else
        if (key == GLFW_KEY_S && action != GLFW_RELEASE) {
            app->moveCamera('b', (mods == 1) ? 0.3 : 0.1);
        }
    else
        if (key == GLFW_KEY_D && action != GLFW_RELEASE) {
            app->moveCamera('r', (mods == 1) ? 0.3 : 10.0);
        }
    else
        if (key == GLFW_KEY_A && action != GLFW_RELEASE) {
            app->moveCamera('l', (mods == 1) ? 0.3 : 0.1);
        }
    else
        if (key == GLFW_KEY_SPACE && action != GLFW_RELEASE) {
            app->moveCamera('u', (mods == 1) ? 0.3 : 0.1);
        }
    else
        if (key == GLFW_KEY_LEFT_CONTROL && action != GLFW_RELEASE) {
            app->moveCamera('d', (mods == 1) ? 0.3 : 0.1);
        }
    else
        if (key == GLFW_KEY_LEFT_CONTROL && action != GLFW_RELEASE) {
            app->moveCamera('d', (mods == 1) ? 0.3 : 0.1);
        }
    else
        if (key == GLFW_KEY_LEFT_CONTROL && action != GLFW_RELEASE) {
            app->moveCamera('d', (mods == 1) ? 0.3 : 0.1);
        }
    else
        if (key == GLFW_KEY_RIGHT&& action == GLFW_PRESS) {
            app->changeScene('+');
        }
    else
        if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
            app->changeScene('-');
        }
    
}

void Controller::handleMouseInput(double xpos, double ypos) {
    // Zpracování vstupu z myši
    app->rotateCamera(xpos, ypos);
}
