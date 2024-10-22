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

	moveLightSourceForward = false;
	moveLightSourceBackward = false;
	moveLightSourceRight = false;
	moveLightSourceLeft = false;
	moveLightSourceUp = false;
	moveLightSourceDown = false;
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

    case GLFW_KEY_KP_8:
        if (action == GLFW_PRESS)
            moveLightSourceForward = true;
        else if (action == GLFW_RELEASE)
            moveLightSourceForward = false;
        break;

    case GLFW_KEY_KP_2:
        if (action == GLFW_PRESS)
            moveLightSourceBackward = true;
        else if (action == GLFW_RELEASE)
            moveLightSourceBackward = false;
        break;

    case GLFW_KEY_KP_6:
        if (action == GLFW_PRESS)
            moveLightSourceRight = true;
        else if (action == GLFW_RELEASE)
            moveLightSourceRight = false;
        break;

    case GLFW_KEY_KP_4:
        if (action == GLFW_PRESS)
            moveLightSourceLeft = true;
        else if (action == GLFW_RELEASE)
            moveLightSourceLeft = false;
        break;

    case GLFW_KEY_KP_ADD:
        if (action == GLFW_PRESS)
            moveLightSourceUp = true;
        else if (action == GLFW_RELEASE)
            moveLightSourceUp = false;
        break;

    case GLFW_KEY_KP_SUBTRACT:
        if (action == GLFW_PRESS)
            moveLightSourceDown = true;
        else if (action == GLFW_RELEASE)
            moveLightSourceDown = false;
        break;

    default:
        break;
    }


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
}

void Controller::updateLightSource() {
	if (moveLightSourceForward)
		app->moveLightSource('f', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
	if (moveLightSourceBackward)
		app->moveLightSource('b', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
	if (moveLightSourceRight)
		app->moveLightSource('r', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
	if (moveLightSourceLeft)
		app->moveLightSource('l', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
	if (moveLightSourceUp)
		app->moveLightSource('u', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
	if (moveLightSourceDown)
		app->moveLightSource('d', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
}
