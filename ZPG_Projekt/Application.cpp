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


    glfwSwapInterval(1);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, CursorCallback);
    glfwSetMouseButtonCallback(window, ButtonCallback);
    glfwSetWindowFocusCallback(window, WindowFocusCallback);
    glfwSetWindowIconifyCallback(window, WindowIconifyCallback);
    glfwSetWindowSizeCallback(window, ResizeCallback);


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


void Application::CreateShaders() {

    this->shaders.push_back(ShaderProgram());

    shaders[0].addVertexShader(std::make_shared<Shader>(GL_VERTEX_SHADER,
        "#version 330\n"
        "layout(location=0) in vec3 vp;"

        "uniform mat4 modelMatrix;"
        "uniform mat4 viewMatrix;"
        "uniform mat4 projectionMatrix;"

        "void main () {"
            "gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);"
        "}"
    ));
    shaders[0].addFragmentShader(std::make_shared<Shader>(GL_FRAGMENT_SHADER,
        "#version 330\n"
        "out vec4 frag_colour;"
        "void main () {"
        "     frag_colour = vec4 (0.0, 1.0, 0.0, 1.0);"
        "}"
    ));

    shaders[0].compile();
    /*
    this->shaders.push_back(ShaderProgram());

    shaders[1].addVertexShader(std::make_shared<Shader>(GL_VERTEX_SHADER,
        "#version 330\n"
        "layout(location=0) in vec3 vp;"

        "uniform mat4 modelMatrix;"
        "uniform mat4 viewMatrix;"
        "uniform mat4 projectionMatrix;"

        "void main () {"
            "gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);"
        "}"
    ));
    shaders[1].addFragmentShader(std::make_shared<Shader>(GL_FRAGMENT_SHADER,
        "#version 330\n"
        "out vec4 frag_colour;"
        "void main () {"
        "     frag_colour = vec4 (0.0, 0.0, 1.0, 1.0);"
        "}"
    ));

    shaders[1].compile();

    this->shaders.push_back(ShaderProgram());

    shaders[2].addVertexShader(std::make_shared<Shader>(GL_VERTEX_SHADER,
        "#version 330\n"
        "layout(location = 0) in vec3 vp;"
        "layout(location = 1) in vec3 vn;"

        "out vec3 fragPos;"
        "out vec3 fragNormal;"
        "uniform mat4 modelMatrix;"
        "uniform mat4 viewMatrix;"
        "uniform mat4 projectionMatrix;"

        "void main() {"
            "fragNormal = vn;"
            "fragPos = vec3(modelMatrix * vec4(vp, 1.0));"
            "gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);"
        "}"
    ));
    shaders[2].addFragmentShader(std::make_shared<Shader>(GL_FRAGMENT_SHADER,
        "#version 330\n"
        "in vec3 fragNormal;"
        "in vec3 fragPos;"

        "out vec4 frag_colour;"

        "void main () {"
        "frag_colour = vec4(fragPos, 1.0);"
        "}"
    ));

    shaders[2].compile();

    this->shaders.push_back(ShaderProgram());

    shaders[3].addVertexShader(std::make_shared<Shader>(GL_VERTEX_SHADER,
        "#version 330\n"
        "layout(location = 0) in vec3 vp;"
        "layout(location = 1) in vec3 vn;"

        "out vec3 fragPos;"
        "out vec3 fragNormal;"
        "uniform mat4 modelMatrix;"
        "uniform mat4 viewMatrix;"
        "uniform mat4 projectionMatrix;"

        "void main() {"
            "fragNormal = vn;"
            "fragPos = vec3(modelMatrix * vec4(vp, 1.0));"
            "gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);"
        "}"
    ));
    shaders[3].addFragmentShader(std::make_shared<Shader>(GL_FRAGMENT_SHADER,
        "#version 330\n"
        "in vec3 fragNormal;"
        "in vec3 fragPos;"

        "out vec4 frag_colour;"

        "void main () {"
        "frag_colour = vec4(fragNormal, 1.0);"
        "}"
    ));

    shaders[3].compile();

    this->shaders.push_back(ShaderProgram());

    shaders[4].addVertexShader(std::make_shared<Shader>(GL_VERTEX_SHADER,
        "#version 330\n"
        "layout(location = 0) in vec3 vp;"
        "layout(location = 1) in vec3 vn;"

        "out vec3 fragPos;"
        "out vec3 fragNormal;"
        "uniform mat4 modelMatrix;"
        "uniform mat4 viewMatrix;"
        "uniform mat4 projectionMatrix;"

        "void main() {"
            "fragNormal = vn;"
            "fragPos = vec3(modelMatrix * vec4(vp, 1.0));"
            "gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);"
        "}"
    ));
    shaders[4].addFragmentShader(std::make_shared<Shader>(GL_FRAGMENT_SHADER,
        "#version 330\n"
        "in vec3 fragNormal;"
        "in vec3 fragPos;"

        "out vec4 frag_colour;"

        "void main () {"
        "frag_colour = vec4(fragNormal, 1.0);"
        "}"
    ));

    shaders[4].compile();
    */
}

void Application::CreateModels() {

    float points1[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
    };

    float points2[] = {
        0.0f, 0.6f, -0.2f,
        0.6f, 0.6f, -0.2f,
        0.6f, 0.0f, -0.2f,
        0.0f, 0.6f, -0.2f,
        0.6f, 0.0f, -0.2f,
        0.0f, 0.0f, -0.2f
    };

    models.push_back(std::make_shared<MyApp::Model>(points1, 3, false));
    models.push_back(std::make_shared<MyApp::Model>(points2, 6, false));
    models.push_back(std::make_shared<MyApp::Model>(sphere, 2880, true));

    models.push_back(std::make_shared<MyApp::Model>(tree, 92814, true));
    models.push_back(std::make_shared<MyApp::Model>(bushes, 8730, true));

    // SCENES
    scenes.push_back(Scene());
    scenes.push_back(Scene());
    scenes.push_back(Scene());

    // 1

    scenes[0].AddObject(std::make_shared<DrawableObject>(models[0], shaders[0]));
    /*
    scenes[0].AddObject(std::make_shared<DrawableObject>(models[1], shaders[1]));
    scenes[0].AddObject(std::make_shared<DrawableObject>(models[2], shaders[2]));

    // 2
    float scaleX, scaleY, scaleZ, transX, transZ, angle, rotX, rotY, rotZ;
    // Trees
    int from, to;
    from = scenes[1].objects.size();
    to = scenes[1].objects.size() + 30;
    for (int i = from; i < to; i++) {
        scaleX = randomFloat(0.05, 0.15);
        scaleY = randomFloat(0.05, 0.15);
        scaleZ = randomFloat(0.05, 0.15);
        transX = randomFloat(-17.0, 17.0);
        transZ = randomFloat(0.0, 7.0);
        angle = randomFloat(-20.0, 20.0);
        rotX = randomFloat(0.0, 1.0);
        rotY = randomFloat(0.0, 1.0);
        rotZ = randomFloat(0.0, 1.0);
        scenes[1].AddObject(std::make_shared<DrawableObject>(models[3], shaders[3]));
        scenes[1].objects[i]->relativeScale(glm::vec3(scaleX, scaleY, scaleZ));
        scenes[1].objects[i]->relativeTranslate(glm::vec3(transX, 0.0f, transZ));
        scenes[1].objects[i]->relativeRotate(glm::radians(angle), glm::vec3(rotX, rotY, rotZ));
    }
    // Bushes
    from = scenes[1].objects.size();
    to = scenes[1].objects.size() + 30;
    for (int i = from; i < to; i++) {
        scaleX = randomFloat(0.4, 0.8);
        scaleY = randomFloat(0.4, 0.8);
        scaleZ = randomFloat(0.4, 0.8);
        transX = randomFloat(-10.0, 10.0);
        transZ = randomFloat(-1.5, 1.5);
        angle = randomFloat(-20.0, 20.0);
        rotX = randomFloat(0.0, 1.0);
        rotY = randomFloat(0.0, 1.0);
        rotZ = randomFloat(0.0, 1.0);
        scenes[1].AddObject(std::make_shared<DrawableObject>(models[4], shaders[4]));
        scenes[1].objects[i]->relativeScale(glm::vec3(scaleX, scaleY, scaleZ));
        scenes[1].objects[i]->relativeTranslate(glm::vec3(transX, 0.0f, transZ));
        scenes[1].objects[i]->relativeRotate(glm::radians(angle), glm::vec3(rotX, rotY, rotZ));
    }

    // 3

    std::shared_ptr<DrawableObjectGroup> group1 = std::make_shared<DrawableObjectGroup>();
    group1->addDrawable(std::make_shared<DrawableObject>(models[0], shaders[0]));
    group1->addDrawable(std::make_shared<DrawableObject>(models[1], shaders[1]));
    group1->addDrawable(std::make_shared<DrawableObject>(models[2], shaders[2]));

    group1->drawables[2]->relativeScale(glm::vec3(0.3f, 0.3f, 0.3f));

    scenes[2].AddObject(group1);

    // TRANSFORMATIONS
    
    //setTranslation(glm::vec3(0.0f, 1.0f, 0.0f));
    //setRotation(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //setScale(glm::vec3(1.0f, 2.0f, 1.0f));
    

    scenes[0].objects[2]->relativeScale(glm::vec3(0.3f, 0.3f, 0.3f));
    */
}

void Application::Run() {
    while (!glfwWindowShouldClose(window)) {
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Enable alfa canal and color blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.

        scenes[currentSceneNumber].Render();

        //scenes[2].objects[0]->relativeRotate(glm::radians(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));

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
    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

    

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
    //printf("CursorCallback \n");
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
            scenes[currentSceneNumber].camera->moveForward(distance);
        }break;
        case'b': {
            scenes[currentSceneNumber].camera->moveBackward(distance);
        }break;
        case'r': {
            scenes[currentSceneNumber].camera->moveRight(distance);
        }break;
        case'l': {
            scenes[currentSceneNumber].camera->moveLeft(distance);
        }break;
        case'u': {
            scenes[currentSceneNumber].camera->moveUp(distance);
        }break;
        case'd': {
            scenes[currentSceneNumber].camera->moveDown(distance);
        }break;
    }
}

void Application::rotateCamera(double xpos, double ypos) {

}


