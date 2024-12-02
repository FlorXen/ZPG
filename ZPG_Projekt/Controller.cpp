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

    case GLFW_KEY_DELETE:
        if (action == GLFW_PRESS) {
            app->getCurrentScene()->deleteSelected();
        }
        break;

    case GLFW_KEY_V:
        if (action == GLFW_PRESS && (mods & GLFW_MOD_CONTROL)) {
            int windowWidth, windowHeight;
            glfwGetWindowSize(app->window, &windowWidth, &windowHeight);

            double xpos, ypos;
            glfwGetCursorPos(app->window, &xpos, &ypos);

            // Get depth from z-buffer
            GLfloat depth;
            glReadPixels(xpos, windowHeight - ypos, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

            glm::vec3 screenX = glm::vec3(xpos, windowHeight - ypos, depth);
            glm::mat4 view = app->getCurrentScene()->camera->getViewMatrix();
            glm::mat4 projection = app->getCurrentScene()->camera->getProjectionMatrix();
            glm::vec4 viewPort = glm::vec4(0, 0, windowWidth, windowHeight);
            glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

            printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);

            app->getCurrentScene()->pasteSelected(pos);

        }
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

    if (firstMouse) {
        cursor.x = (float)xpos;
        cursor.y = (float)ypos;
        firstMouse = false;
    }

    // Count position difference
    xOffset = (float)xpos - cursor.x;
    yOffset = cursor.y - (float)ypos;

    cursor.x = (float)xpos;
    cursor.y = (float)ypos;

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

        int windowWidth, windowHeight;
        glfwGetWindowSize(app->window, &windowWidth, &windowHeight);

        double xpos = windowWidth / 2.0;
        double ypos = windowHeight / 2.0;
        glfwSetCursorPos(app->window, xpos, ypos);

        cursor.x = xpos;
        cursor.y = ypos;
        xOffset = 0;
        yOffset = 0;
        
    }

    if (button == 0 && action == 0) {
        GLbyte color[4];
        GLfloat depth;
        GLuint index;

        GLint x = (GLint)cursor.x;
        GLint y = (GLint)cursor.y;


        int newy = app->getCurrentScene()->camera->getResolution().y - y;

        glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
        app->getCurrentScene()->setSelect(index);
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
