#include "Application.h"
#include "Shader.h"

Application::Application(int w, int h) : width(w), height(h) {
}

Application::~Application() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void APIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::cerr << "OpenGL Debug Message: " << message << std::endl;
}

void Application::Initialize() {

    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetWindowUserPointer(window, this);

    glfwMakeContextCurrent(window);


    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error initializing GLEW: " << glewGetErrorString(err) << std::endl;
    }
    else {
        std::cout << "GLEW initialized successfully!" << std::endl;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(openglDebugCallback, nullptr);

    glfwSwapInterval(1);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, CursorCallback);
    glfwSetMouseButtonCallback(window, ButtonCallback);
    glfwSetWindowFocusCallback(window, WindowFocusCallback);
    glfwSetWindowIconifyCallback(window, WindowIconifyCallback);
    glfwSetWindowSizeCallback(window, ResizeCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));


    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;
    glViewport(0, 0, width, height);

    controller = Controller(this);
}

void Application::CreateScenes() {

    MyApp::Model model_triangle = MyApp::Model(triangle, 3, false);
    MyApp::Model model_square = MyApp::Model(square, 6, false);
    MyApp::Model model_sphere = MyApp::Model(sphere, 2880, true);
    MyApp::Model model_tree = MyApp::Model(tree, 92814, true);
    MyApp::Model model_bush = MyApp::Model(bushes, 8730, true);
    MyApp::Model model_plain = MyApp::Model(plain, 6, true);


    // SCENES

    // 1
    scenes.push_back(std::make_shared<Scene>());

    scenes[0]->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/basic_triangle.vert", "Shaders/basic_triangle.frag"));
    scenes[0]->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/basic_square.vert", "Shaders/basic_square.frag"));
    scenes[0]->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/basic_sphere.vert", "Shaders/basic_sphere.frag"));

    scenes[0]->AddModel(std::make_shared<MyApp::Model>(model_triangle));
    scenes[0]->AddModel(std::make_shared<MyApp::Model>(model_square));
    scenes[0]->AddModel(std::make_shared<MyApp::Model>(model_sphere));

    scenes[0]->CreateObject(std::make_shared<DrawableObject>(scenes[0]->models[0], scenes[0]->shaders[0]));
    scenes[0]->CreateObject(std::make_shared<DrawableObject>(scenes[0]->models[1], scenes[0]->shaders[1]));
    scenes[0]->CreateObject(std::make_shared<DrawableObject>(scenes[0]->models[2], scenes[0]->shaders[2]));

    scenes[0]->objects[2]->scale(glm::vec3(0.3f, 0.3f, 0.3f));
    
    // 2
    scenes.push_back(std::make_shared<Scene>());

    scenes[1]->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/tree.vert", "Shaders/tree.frag"));
    scenes[1]->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/bush.vert", "Shaders/bush.frag"));
    scenes[1]->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/plain.vert", "Shaders/plain.frag"));

    scenes[1]->AddModel(std::make_shared<MyApp::Model>(model_tree));
    scenes[1]->AddModel(std::make_shared<MyApp::Model>(model_bush));
    scenes[1]->AddModel(std::make_shared<MyApp::Model>(model_plain));

    scenes[1]->CreateObject(std::make_shared<DrawableObject>(scenes[1]->models[2], scenes[1]->shaders[2]));

    scenes[1]->objects[0]->scale(glm::vec3(30.0f, 0.0f, 30.0f));
    
    float scaleX, scaleY, scaleZ, transX, transZ, angle, rotX, rotY, rotZ;
    // Trees
    int from, to;
    from = scenes[1]->objects.size();
    to = scenes[1]->objects.size() + 100;
    for (int i = from; i < to; i++) {
        scaleX = randomFloat(0.4, 0.8);
        scaleY = randomFloat(0.6, 1.3);
        scaleZ = randomFloat(0.4, 0.8);
        transX = randomFloat(-30.0, 30.0);
        transZ = randomFloat(-30.0, 30.0);
        angle = randomFloat(-20.0, 20.0);
        rotX = randomFloat(0.0, 1.0);
        rotY = randomFloat(0.0, 1.0);
        rotZ = randomFloat(0.0, 1.0);
        scenes[1]->CreateObject(std::make_shared<DrawableObject>(scenes[1]->models[0], scenes[1]->shaders[0]));
        scenes[1]->objects[i]->scale(glm::vec3(scaleX, scaleY, scaleZ));
        scenes[1]->objects[i]->translate(glm::vec3(transX, 0.0f, transZ));
        scenes[1]->objects[i]->rotate(glm::radians(angle), glm::vec3(rotX, rotY, rotZ));
    }
    // Bushes
    from = scenes[1]->objects.size();
    to = scenes[1]->objects.size() + 100;
    for (int i = from; i < to; i++) {
        scaleX = randomFloat(0.4, 0.8);
        scaleY = randomFloat(0.6, 1.5);
        scaleZ = randomFloat(0.4, 0.8);
        transX = randomFloat(-30.0, 30.0);
        transZ = randomFloat(-30.0, 30.0);
        angle = randomFloat(-20.0, 20.0);
        rotX = randomFloat(0.0, 1.0);
        rotY = randomFloat(0.0, 1.0);
        rotZ = randomFloat(0.0, 1.0);
        scenes[1]->CreateObject(std::make_shared<DrawableObject>(scenes[1]->models[1], scenes[1]->shaders[1]));
        scenes[1]->objects[i]->scale(glm::vec3(scaleX, scaleY, scaleZ));
        scenes[1]->objects[i]->translate(glm::vec3(transX, 0.0f, transZ));
        scenes[1]->objects[i]->rotate(glm::radians(angle), glm::vec3(rotX, rotY, rotZ));
    }

    
    // 3
    scenes.push_back(std::make_shared<Scene>());

    scenes[2]->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/basic_triangle.vert", "Shaders/basic_triangle.frag"));
    scenes[2]->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/basic_square.vert", "Shaders/basic_square.frag"));
    scenes[2]->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/basic_sphere.vert", "Shaders/basic_sphere.frag"));

    scenes[2]->AddModel(std::make_shared<MyApp::Model>(model_triangle));
    scenes[2]->AddModel(std::make_shared<MyApp::Model>(model_square));
    scenes[2]->AddModel(std::make_shared<MyApp::Model>(model_sphere));

    scenes[2]->CreateObject(std::make_shared<DrawableObjectGroup>());

    scenes[2]->objects[0]->addDrawable(std::make_shared<DrawableObject>(scenes[2]->models[0], scenes[2]->shaders[0]));
    scenes[2]->objects[0]->addDrawable(std::make_shared<DrawableObject>(scenes[2]->models[1], scenes[2]->shaders[1]));
    scenes[2]->objects[0]->addDrawable(std::make_shared<DrawableObject>(scenes[2]->models[2], scenes[2]->shaders[2]));

    scenes[2]->objects[0]->getDrawables().at(2)->scale(glm::vec3(0.3f, 0.3f, 0.3f));
    
    //4
    scenes.push_back(std::make_shared<Scene>());

    scenes[3]->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/light_sphere.vert", "Shaders/light_sphere.frag"));

    scenes[3]->AddModel(std::make_shared<MyApp::Model>(model_sphere));

    scenes[3]->CreateObject(std::make_shared<DrawableObject>(scenes[3]->models[0], scenes[3]->shaders[0]));
    scenes[3]->CreateObject(std::make_shared<DrawableObject>(scenes[3]->models[0], scenes[3]->shaders[0]));
    scenes[3]->CreateObject(std::make_shared<DrawableObject>(scenes[3]->models[0], scenes[3]->shaders[0]));
    scenes[3]->CreateObject(std::make_shared<DrawableObject>(scenes[3]->models[0], scenes[3]->shaders[0]));

    scenes[3]->objects[0]->translate(glm::vec3(2.5f, 0.0f, 0.0f));
    scenes[3]->objects[1]->translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    scenes[3]->objects[2]->translate(glm::vec3(0.0f, 0.0f, 2.5f));
    scenes[3]->objects[3]->translate(glm::vec3(0.0f, 0.0f, -2.5f));

    // TRANSFORMATIONS
    //setTranslation(glm::vec3(0.0f, 1.0f, 0.0f));
    //setRotation(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //setScale(glm::vec3(1.0f, 2.0f, 1.0f));

}

void Application::Run() {
    bool shrinking = true;
    float currentScale = 1.0f;
    const float minScale = 0.5f;
    const float maxScale = 1.5f;
    const float scaleSpeed = 0.01f;

    while (!glfwWindowShouldClose(window)) {
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Enable alfa canal and color blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.

        controller.updateCamera();

        scenes[currentSceneNumber]->Render();
        
        scenes[2]->objects[0]->rotate(glm::radians(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        if (shrinking) {
            if (currentScale > minScale) {
                currentScale -= scaleSpeed;
                scenes[2]->objects[0]->getDrawables().at(0)->scale(glm::vec3(1.0f - scaleSpeed, 1.0f - scaleSpeed, 1.0f - scaleSpeed));
            }
            else {
                shrinking = false;
            }
        }
        else {
            if (currentScale < maxScale) {
                currentScale += scaleSpeed;
                scenes[2]->objects[0]->getDrawables().at(0)->scale(glm::vec3(1.0f + scaleSpeed, 1.0f + scaleSpeed, 1.0f + scaleSpeed));
            }
            else {
                shrinking = true;
            }
        }
        
        

        // update other events like input handling
        glfwPollEvents();
        // put the stuff we�ve been drawing onto the display
        glfwSwapBuffers(window);

    }
}

void Application::ErrorCallback(int error, const char* description) {
    fputs(description, stderr);
}

void Application::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    //printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

    if (app) {
        app->controller.handleKeyInput(key, scancode, action, mods);
    }
}

void Application::ResizeCallback(GLFWwindow* window, int width, int height) {
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);
}

void Application::ButtonCallback(GLFWwindow* window, int button, int action, int mode) {
    if (action == GLFW_PRESS) {
        printf("button_callback [%d,%d,%d]\n", button, action, mode);
    }
}

void Application::WindowFocusCallback(GLFWwindow* window, int focused) {
    printf("WindowFocusCallback \n");
}

void Application::WindowIconifyCallback(GLFWwindow* window, int iconified) {
    printf("WindowIconifyCallback \n");
}

void Application::CursorCallback(GLFWwindow* window, double x, double y) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->controller.handleMouseInput(x, y);
    }
}

float Application::randomFloat(float min, float max) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);

    return dis(gen);
}

void Application::changeScene(char sign) {
    switch (sign) {
        case'+': {
            if (currentSceneNumber + 1 > scenes.size() - 1)
                currentSceneNumber = 0;
            else
                currentSceneNumber++;
        }break;
        case'-': {
            if (currentSceneNumber - 1 < 0)
                currentSceneNumber = (int)scenes.size() - 1;
            else
                currentSceneNumber--;
        }break;
    }
}

void Application::moveCamera(char direction, float distance) {
    switch (direction) {
        case'f': {
            scenes[currentSceneNumber]->camera->moveForward(distance);
        }break;
        case'b': {
            scenes[currentSceneNumber]->camera->moveBackward(distance);
        }break;
        case'r': {
            scenes[currentSceneNumber]->camera->moveRight(distance);
        }break;
        case'l': {
            scenes[currentSceneNumber]->camera->moveLeft(distance);
        }break;
        case'u': {
            scenes[currentSceneNumber]->camera->moveUp(distance);
        }break;
        case'd': {
            scenes[currentSceneNumber]->camera->moveDown(distance);
        }break;
    }
}

void Application::rotateCamera(float xOffset, float yOffset) {
    scenes[currentSceneNumber]->camera->setOrientation(scenes[currentSceneNumber]->camera->getAlpha() - yOffset, scenes[currentSceneNumber]->camera->getFi() + xOffset);
}


