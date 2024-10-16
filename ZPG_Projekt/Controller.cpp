#include "Controller.h"
#include "Application.h"

Controller::Controller(Application* app) : app(app) {
	mode = 0;

	moveForward = false;
	moveBackward = false;
	moveRight = false;
	moveLeft = false;
	moveUp = false;
	moveDown = false;
}

void Controller::handleKeyInput(int key, int scancode, int action, int mods) {

	mode = mods;

	if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS)
			moveForward = true;
		if (action == GLFW_RELEASE)
			moveForward = false;
	}
	else
		if (key == GLFW_KEY_S) {
			if (action == GLFW_PRESS)
				moveBackward = true;
			if (action == GLFW_RELEASE)
				moveBackward = false;
		}
		else
			if (key == GLFW_KEY_D) {
				if (action == GLFW_PRESS)
					moveRight = true;
				if (action == GLFW_RELEASE)
					moveRight = false;
			}
			else
				if (key == GLFW_KEY_A) {
					if (action == GLFW_PRESS)
						moveLeft = true;
					if (action == GLFW_RELEASE)
						moveLeft = false;
				}
				else
					if (key == GLFW_KEY_SPACE) {
						if (action == GLFW_PRESS)
							moveUp = true;
						if (action == GLFW_RELEASE)
							moveUp = false;
					}
					else
						if (key == GLFW_KEY_LEFT_SHIFT) {
							if (action == GLFW_PRESS)
								moveDown = true;
							if (action == GLFW_RELEASE)
								moveDown = false;
						}
						else
							if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
								app->changeScene('+');
							}
							else
								if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
									app->changeScene('-');
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
}

void Controller::updateCamera() {
	if (moveForward)
		app->moveCamera('f', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
	if (moveBackward)
		app->moveCamera('b', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
	if (moveRight)
		app->moveCamera('r', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
	if (moveLeft)
		app->moveCamera('l', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
	if (moveUp)
		app->moveCamera('u', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);
	if (moveDown)
		app->moveCamera('d', (mode == GLFW_MOD_CONTROL) ? 0.15 : 0.05);

	app->rotateCamera(xOffset, yOffset);
	xOffset = 0;
	yOffset = 0;
}
