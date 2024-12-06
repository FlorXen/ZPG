#pragma once
#define GLM_ENABLE_EXPERIMENTAL
//Include GLEW
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "DrawableObject.h"
#include "DrawableObjectGroup.h"
#include "Controller.h"
#include "Flashlight.h"
#include "AssimpDrawableObject.h"
#include "AssimpModel.h"

#include "Models/triangle.h"
#include "Models/square.h"
#include "Models/sphere.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/plain.h"
#include "Models/skycube.h"

#include <random>
#include <iostream>
#include <memory>

class Shader;

class Application {
private:
    std::vector<std::shared_ptr<Scene>> scenes;

    int width, height, currentSceneNumber = 0;
    bool isDay = true;

    static float randomFloat(double min, double max);

public:
    GLFWwindow* window;
    Controller controller = nullptr;

    Application(int w = 1600, int h = 800);
    ~Application();

    void Initialize();
    void CreateScenes();
    void Run();

    static void ErrorCallback(int error, const char* description);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void ResizeCallback(GLFWwindow* window, int width, int height);
    static void ButtonCallback(GLFWwindow* window, int button, int action, int mode);
    static void WindowFocusCallback(GLFWwindow* window, int focused);
    static void WindowIconifyCallback(GLFWwindow* window, int iconified);
    static void CursorCallback(GLFWwindow* window, double x, double y);

    void changeScene(char sign);

    void moveCamera(char direction, float distance);
    void rotateCamera(float alphaAngle, float fiAngle);
    void lockCursor(bool lock);

    void updateWindowSizeInScenes(int width, int height);

    void changeDateTimeInForest();

    std::shared_ptr<Scene> getCurrentScene();
};