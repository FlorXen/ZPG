#pragma once

//Include GLEW
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  

#include "Scene.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "DrawableObjectGroup.h"
#include "Controller.h"

#include "triangle.h"
#include "square.h"
#include "sphere.h"
#include "tree.h"
#include "bushes.h"
#include "plain.h"

#include <random>
#include <iostream>
#include <memory>

class Shader;

class Application {
private:
    GLFWwindow* window;
    std::vector<std::shared_ptr<Scene>> scenes;

    int width, height, currentSceneNumber = 0;

    static float randomFloat(double min, double max);

public:

    Controller controller = nullptr;

    Application(int w = 800, int h = 600);
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

    void moveLightSource(char direction, float distance);
};