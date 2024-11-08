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
	static bool firstMouse = true;
	static double lastX = xpos;
	static double lastY = ypos;

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	// Count position difference
	xOffset = xpos - lastX;
	yOffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	// Mouse sensitivity
	const float sensitivity = 0.005f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	mouseChanged = true;
}

void Controller::updateCamera() {
	if (moveCameraForward)
		app->moveCamera('f', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
	if (moveCameraBackward)
		app->moveCamera('b', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
	if (moveCameraRight)
		app->moveCamera('r', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
	if (moveCameraLeft)
		app->moveCamera('l', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
	if (moveCameraUp)
		app->moveCamera('u', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
	if (moveCameraDown)
		app->moveCamera('d', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);

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
