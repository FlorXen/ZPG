#include "Controller.h"
#include "Application.h"

Controller::Controller(Application* app) : app(app) {
	mode = 0;

	moveCameraForward = false;
	moveCameraBackward = false;
	moveCameraRight = false;
	moveCameraLeft = false;
	moveCameraUp = false;
	moveCameraDown = false;

    cursorLocked = false;

    mouseChanged = false;
    xOffset = 0;
    yOffset = 0;

    windowWidth = 0;
    windowHeight = 0;
    windowSizeChanged = false;
}

void Controller::handleKeyInput(int key, int scancode, int action, int mods) {

	mode = mods;

    switch (key) {
    case GLFW_KEY_W:
        if (action == GLFW_PRESS)
            moveCameraForward = true;
        else if (action == GLFW_RELEASE)
            moveCameraForward = false;
        break;

    case GLFW_KEY_S:
        if (action == GLFW_PRESS)
            moveCameraBackward = true;
        else if (action == GLFW_RELEASE)
            moveCameraBackward = false;
        break;

    case GLFW_KEY_D:
        if (action == GLFW_PRESS)
            moveCameraRight = true;
        else if (action == GLFW_RELEASE)
            moveCameraRight = false;
        break;

    case GLFW_KEY_A:
        if (action == GLFW_PRESS)
            moveCameraLeft = true;
        else if (action == GLFW_RELEASE)
            moveCameraLeft = false;
        break;

    case GLFW_KEY_SPACE:
        if (action == GLFW_PRESS)
            moveCameraUp = true;
        else if (action == GLFW_RELEASE)
            moveCameraUp = false;
        break;

    case GLFW_KEY_LEFT_SHIFT:
        if (action == GLFW_PRESS)
            moveCameraDown = true;
        else if (action == GLFW_RELEASE)
            moveCameraDown = false;
        break;

    case GLFW_KEY_RIGHT:
        if (action == GLFW_PRESS)
            app->changeScene('+');
        break;

    case GLFW_KEY_LEFT:
        if (action == GLFW_PRESS)
            app->changeScene('-');
        break;

    default:
        break;
    }


}

void Controller::handleWindowResize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    windowSizeChanged = true;
}

void Controller::handleMouseInput(double xpos, double ypos) {
    static bool firstMouse = false;
    static float lastX = (float)xpos;
    static float lastY = (float)ypos;

        if (firstMouse) {
            lastX = (float)xpos;
            lastY = (float)ypos;
            firstMouse = false;
        }

        // Count position difference
        xOffset = (float)xpos - lastX;
        yOffset = lastY - (float)ypos;

        lastX = (float)xpos;
        lastY = (float)ypos;

        // Mouse sensitivity
        const float sensitivity = 0.005f;
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        mouseChanged = true;
}

void Controller::handleMouseClickInput(int button, int action, int mode) {
    if (button == 2 && action == 1) {
        app->lockCursor(true);
        cursorLocked = true;
    }
    else if (button == 2 && action == 0) {
        app->lockCursor(false);
        cursorLocked = false;
    }
}

void Controller::updateCamera() {
	if (moveCameraForward)
		app->moveCamera('f', (mode == GLFW_MOD_CONTROL) ? 0.15f : 0.05f);
	if (moveCameraBackward)
		app->moveCamera('b', (mode == GLFW_MOD_CONTROL) ? 0.15f : 0.05f);
	if (moveCameraRight)
		app->moveCamera('r', (mode == GLFW_MOD_CONTROL) ? 0.15f : 0.05f);
	if (moveCameraLeft)
		app->moveCamera('l', (mode == GLFW_MOD_CONTROL) ? 0.15f : 0.05f);
	if (moveCameraUp)
		app->moveCamera('u', (mode == GLFW_MOD_CONTROL) ? 0.15f : 0.05f);
	if (moveCameraDown)
		app->moveCamera('d', (mode == GLFW_MOD_CONTROL) ? 0.15f : 0.05f);

	if (mouseChanged) {
		app->rotateCamera(xOffset, yOffset);
		xOffset = 0;
		yOffset = 0;
		mouseChanged = false;
	}

    if (windowSizeChanged) {
        app->updateWindowSizeInScenes(windowWidth, windowHeight);
        windowSizeChanged = false;
    }

}
