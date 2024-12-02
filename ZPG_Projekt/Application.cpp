#include "Application.h"

Application::Application(int w, int h) : width(w), height(h) {
    window = nullptr;
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

    window = glfwCreateWindow(width, height, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetWindowUserPointer(window, this);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

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

void Application::CreateScenes() {

    // Models
    MyApp::Model model_triangle = MyApp::Model(triangle, 3, false, false);
    MyApp::Model model_square = MyApp::Model(square, 6, false, false);
    MyApp::Model model_sphere = MyApp::Model(sphere, 2880, true, false);
    MyApp::Model model_tree = MyApp::Model(tree, 92814, true, false);
    MyApp::Model model_bush = MyApp::Model(bushes, 8730, true, false);
    MyApp::Model model_plain = MyApp::Model(plain, 6, true, false);
    MyApp::Model model_plain2 = MyApp::Model(plain2, 6, true, true);
    MyApp::Model model_skycube = MyApp::Model(skycube, 36, false, false);
    AssimpModel model_login = AssimpModel("Models/login.obj");
    AssimpModel model_house = AssimpModel("Models/house.obj");
    AssimpModel model_grass = AssimpModel("Models/grass.obj");

    // Textures
    Texture texture_plain = Texture("Textures/forest_plain.jpg", GL_TEXTURE_2D, 1);
    Texture texture_skybox(
        "Textures/posx.jpg",
        "Textures/negx.jpg",
        "Textures/posy.jpg",
        "Textures/negy.jpg",
        "Textures/posz.jpg",
        "Textures/negz.jpg",
        GL_TEXTURE_2D, 2
    );
    Texture texture_wood = Texture("Textures/test.png", GL_TEXTURE_2D, 3);
    Texture texture_house = Texture("Textures/house.png", GL_TEXTURE_2D, 4);
    Texture texture_grass = Texture("Textures/grass.jpg", GL_TEXTURE_2D, 5);

    // SCENES

    // Scene 0
    {
        scenes.push_back(std::make_shared<Scene>());

        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/basic_triangle.vert", "Shaders/basic_triangle.frag"));
        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/basic_square.vert", "Shaders/basic_square.frag"));
        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/basic_sphere.vert", "Shaders/basic_sphere.frag"));

        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_triangle));
        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_square));
        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_sphere));

        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[0], scenes.back()->shaders[0]));
        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[1], scenes.back()->shaders[1]));
        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[2], scenes.back()->shaders[2]));

        scenes.back()->AddLightSource(std::make_shared<LightSource>());

        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Scale>(glm::vec3(0.3f, 0.3f, 0.3f)));
    }

    // Scene 1 - Forest
    {
        scenes.push_back(std::make_shared<Scene>());

        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/universal.vert", "Shaders/light_tree.frag"));
        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/universal.vert", "Shaders/texture_test.frag"));
        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/universal.vert", "Shaders/skybox.frag"));

        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_tree));
        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_bush));
        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_plain2));
        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_skycube));
        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_house));
        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_grass));
        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_login));

        scenes.back()->AddTexture(std::make_shared<Texture>(texture_plain));
        scenes.back()->AddTexture(std::make_shared<Texture>(texture_skybox));
        scenes.back()->AddTexture(std::make_shared<Texture>(texture_house));
        scenes.back()->AddTexture(std::make_shared<Texture>(texture_grass));
        scenes.back()->AddTexture(std::make_shared<Texture>(texture_wood));

        scenes.back()->AddLightSource(std::make_shared<LightSource>());
        scenes.back()->lightSources.back()->translate(glm::vec3(-10.0f, 3.0f, 10.0f));
        scenes.back()->AddLightSource(std::make_shared<LightSource>());
        scenes.back()->lightSources.back()->translate(glm::vec3(10.0f, 3.0f, 10.0f));
        scenes.back()->AddLightSource(std::make_shared<LightSource>());
        scenes.back()->lightSources.back()->translate(glm::vec3(-10.0f, 3.0f, -10.0f));

        for (std::shared_ptr<LightSource> light : scenes.back()->lightSources) {
            light->randomDynamicTranslate(light->getPosition(), 0.5f, 2.0f, -10.0f, 10.0f, 1.0f, 6.0f, -10.0f, 10.0f);
            light->setAttenuation(glm::vec3(1.0, 0.1, 0.1));
            light->setLightType(LIGHT_POINT);
        }

        // Day - Night setting
        bool isDay = true;
        if (isDay) {
            scenes.back()->setGlobalAmbient(glm::vec4(0.5, 0.5, 0.5, 1));

            scenes.back()->AddLightSource(std::make_shared<LightSource>());
            scenes.back()->lightSources.back()->setLightType(LIGHT_DIRECTION);
            scenes.back()->lightSources.back()->setDirection(glm::vec3(0.0, -1.0, 0.0));
        }

        auto flashlight = std::make_shared<Flashlight>(scenes.back()->camera);
        flashlight->initializeObserver();
        flashlight->setDiffuse(glm::vec4(1.0, 1.0, 1.0, 1.0));
        flashlight->setAttenuation(glm::vec3(0.5, 0.05, 0.05));
        scenes.back()->AddLightSource(flashlight);

        // Plain
        /*scenes[1]->CreateObject(std::make_shared<DrawableObject>(scenes[1]->models[2], scenes[1]->shaders[1]));
        scenes[1]->objects[0]->getTransformation().addTransformation(std::make_shared<Scale>(glm::vec3(30.0)));
        scenes[1]->objects[0]->addTexture(scenes[1]->textures[0]);*/
        scenes.back()->CreateObject(std::make_shared<AssimpDrawableObject>(scenes.back()->models[5], scenes.back()->shaders[1]));
        scenes.back()->objects.back()->addTexture(scenes.back()->textures[3]);
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Rotate>(90.0, glm::vec3(-1.0, 0.0, 0.0)));
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Scale>(glm::vec3(0.2, 0.2, 0.4)));
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(0.0, 0.0, -7.6)));

        // House
        scenes.back()->CreateObject(std::make_shared<AssimpDrawableObject>(scenes.back()->models[4], scenes.back()->shaders[1], scenes.back()->getNextObjectID()));
        scenes.back()->objects.back()->addTexture(scenes.back()->textures[2]);
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Scale>(glm::vec3(0.6, 0.6, 0.6)));

        // Login
        scenes.back()->CreateObject(std::make_shared<AssimpDrawableObject>(scenes.back()->models[6], scenes.back()->shaders[1], scenes.back()->getNextObjectID()));
        scenes.back()->objects.back()->addTexture(scenes.back()->textures[4]);
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(-2.2, 2.0, 6.6)));

        // Skybox
        scenes.back()->setSkybox(std::make_shared<Skybox>(scenes.back()->models[3], scenes.back()->shaders[2], scenes.back()->textures[1]));

        // Trees
        float scaleX, scaleY, scaleZ, transX, transZ, angle, rotX, rotY, rotZ;
        for (int i = 0; i < 200; i++) {
            scaleX = randomFloat(0.4, 0.8);
            scaleY = randomFloat(0.6, 1.3);
            scaleZ = randomFloat(0.4, 0.8);
            do {
                transX = randomFloat(-30.0, 30.0);
                transZ = randomFloat(-30.0, 30.0);
            } while (transX > -7.0 && transX < 7.0 && transZ > -14.0 && transZ < 14.0);
            angle = randomFloat(-20.0, 20.0);
            rotX = randomFloat(0.0, 1.0);
            rotY = randomFloat(0.0, 1.0);
            rotZ = randomFloat(0.0, 1.0);
            scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[0], scenes.back()->shaders[0], scenes.back()->getNextObjectID()));
            scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Scale>(glm::vec3(scaleX, scaleY, scaleZ)));
            scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(transX, 0.0f, transZ)));

            if (i < 10)
                scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<DynamicRotate>(angle, glm::vec3(0.0f, 3.0f, 0.0f)));
            else
                scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Rotate>(angle, glm::vec3(rotX, rotY, rotZ)));
        }

        // Bushes
        for (int i = 0; i < 150; i++) {
            scaleX = randomFloat(1.0, 2.5);
            scaleY = randomFloat(1.0, 2.5);
            scaleZ = randomFloat(1.0, 2.5);
            transX = randomFloat(-30.0, 30.0);
            transZ = randomFloat(-30.0, 30.0);
            angle = randomFloat(-20.0, 20.0);
            rotX = randomFloat(0.0, 1.0);
            rotY = randomFloat(0.0, 1.0);
            rotZ = randomFloat(0.0, 1.0);
            scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[1], scenes.back()->shaders[0]));
            scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(transX, 0.0f, transZ)));
            scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Rotate>(angle, glm::vec3(rotX, rotY, rotZ)));
            scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Scale>(glm::vec3(scaleX, scaleY, scaleZ)));
        }
    }

    // Scene 2
    {
        scenes.push_back(std::make_shared<Scene>());

        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/basic_triangle.vert", "Shaders/basic_triangle.frag"));
        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/basic_square.vert", "Shaders/basic_square.frag"));
        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/basic_sphere.vert", "Shaders/basic_sphere.frag"));

        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_triangle));
        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_square));
        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_sphere));

        scenes.back()->CreateObject(std::make_shared<DrawableObjectGroup>());

		scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<DynamicRotate>(20.0 ,glm::vec3(1.0f, 0.0f, 0.0f)));

        scenes.back()->objects.back()->addDrawable(std::make_shared<DrawableObject>(scenes.back()->models[0], scenes.back()->shaders[0]));
        scenes.back()->objects.back()->addDrawable(std::make_shared<DrawableObject>(scenes.back()->models[1], scenes.back()->shaders[1]));
        scenes.back()->objects.back()->addDrawable(std::make_shared<DrawableObject>(scenes.back()->models[2], scenes.back()->shaders[2]));

        scenes.back()->AddLightSource(std::make_shared<LightSource>());
        scenes.back()->lightSources.back()->setLightType(LIGHT_POINT);

        scenes.back()->objects.back()->getDrawables().at(2)->getTransformation().addTransformation(std::make_shared<Scale>(glm::vec3(0.3f, 0.3f, 0.3f)));
    }

    // Scene 3
    {
        scenes.push_back(std::make_shared<Scene>());

        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/universal.vert", "Shaders/light_Phong.frag"));

        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_sphere));

        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[0], scenes.back()->shaders[0]));
        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[0], scenes.back()->shaders[0]));
        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[0], scenes.back()->shaders[0]));
        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[0], scenes.back()->shaders[0]));

        scenes.back()->objects[0]->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(2.5f, 0.0f, 0.0f)));
        scenes.back()->objects[1]->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(-2.5f, 0.0f, 0.0f)));
        scenes.back()->objects[2]->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(0.0f, 0.0f, 2.5f)));
        scenes.back()->objects[3]->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(0.0f, 0.0f, -2.5f)));

        scenes.back()->AddLightSource(std::make_shared<LightSource>());
        scenes.back()->lightSources.back()->setLightType(LIGHT_POINT);

        auto flashlight = std::make_shared<Flashlight>(scenes.back()->camera);
        flashlight->initializeObserver();
        scenes.back()->AddLightSource(flashlight);
    }

    // Scene 4
    {
        scenes.push_back(std::make_shared<Scene>());

        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/universal.vert", "Shaders/light_sphere.frag"));

        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_sphere));

        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[0], scenes.back()->shaders[0]));

        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(0.0f, 0.0f, 0.0f)));

        scenes.back()->AddLightSource(std::make_shared<LightSource>());
        scenes.back()->lightSources.back()->setLightType(LIGHT_POINT);
        scenes.back()->lightSources.back()->translate(glm::vec3(0.0f, 0.0f, -3.0f));

        scenes.back()->camera->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    }

    // Scene 5
    {
        scenes.push_back(std::make_shared<Scene>());

        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/universal.vert", "Shaders/light_constant.frag"));
        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/universal.vert", "Shaders/light_Lambert.frag"));
        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/universal.vert", "Shaders/light_Phong.frag"));
        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/universal.vert", "Shaders/light_Blinn.frag"));

        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_sphere));
        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_tree));

        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[0], scenes.back()->shaders[0]));
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(-6.5f, 0.0f, 0.0f)));
        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[0], scenes.back()->shaders[1]));
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(-2.5f, 0.0f, 0.0f)));
        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[0], scenes.back()->shaders[2]));
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(2.5f, 0.0f, 0.0f)));
        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[0], scenes.back()->shaders[3]));
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(6.5f, 0.0f, 0.0f)));
        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[1], scenes.back()->shaders[0]));
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(-6.5f, 0.0f, 0.0f)));
        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[1], scenes.back()->shaders[1]));
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(-2.5f, 0.0f, 0.0f)));
        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[1], scenes.back()->shaders[2]));
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(2.5f, 0.0f, 0.0f)));
        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[1], scenes.back()->shaders[3]));
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(6.5f, 0.0f, 0.0f)));


        scenes.back()->AddLightSource(std::make_shared<LightSource>());
        scenes.back()->lightSources.back()->setLightType(LIGHT_POINT);
        scenes.back()->lightSources.back()->translate(glm::vec3(0.0f, 0.0f, 8.0f));

    }

    // Scene 6
    {
        scenes.push_back(std::make_shared<Scene>());
        scenes.back()->setGlobalAmbient(glm::vec4(1.0, 1.0, 1.0, 1.0));

        scenes.back()->AddShaderProgram(std::make_shared<ShaderProgram>("Shaders/universal.vert", "Shaders/texture_test.frag"));

        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_plain2));
        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_login));
        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_house));
        scenes.back()->AddModel(std::make_shared<MyApp::Model>(model_grass));

        scenes.back()->AddTexture(std::make_shared<Texture>(texture_plain));
        scenes.back()->AddTexture(std::make_shared<Texture>(texture_wood));
        scenes.back()->AddTexture(std::make_shared<Texture>(texture_house));
        scenes.back()->AddTexture(std::make_shared<Texture>(texture_grass));

        scenes.back()->CreateObject(std::make_shared<DrawableObject>(scenes.back()->models[0], scenes.back()->shaders[0]));
        scenes.back()->objects.back()->addTexture(scenes.back()->textures[0]);

        scenes.back()->CreateObject(std::make_shared<AssimpDrawableObject>(scenes.back()->models[1], scenes.back()->shaders[0]));
        scenes.back()->objects.back()->addTexture(scenes.back()->textures[1]);

        scenes.back()->CreateObject(std::make_shared<AssimpDrawableObject>(scenes.back()->models[2], scenes.back()->shaders[0]));
        scenes.back()->objects.back()->addTexture(scenes.back()->textures[2]);
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Scale>(glm::vec3(0.6, 0.6, 0.6)));

        scenes.back()->CreateObject(std::make_shared<AssimpDrawableObject>(scenes.back()->models[3], scenes.back()->shaders[0]));
        scenes.back()->objects.back()->addTexture(scenes.back()->textures[3]);
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Rotate>(90.0, glm::vec3(-1.0, 0.0, 0.0)));
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Scale>(glm::vec3(0.5, 0.5, 0.4)));
        scenes.back()->objects.back()->getTransformation().addTransformation(std::make_shared<Translate>(glm::vec3(0.0, 0.0, -7.6)));
    }

    for (std::shared_ptr<Scene> sc : scenes) {
        sc->camera->setWindowSize(width, height);
    }

}

void Application::Run() {

    glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    while (!glfwWindowShouldClose(window)) {
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Enable alfa canal and color blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        controller.updateCamera();

        scenes[currentSceneNumber]->Render();
        
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
    //printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);

    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->controller.handleWindowResize(width, height);
    }
}

void Application::ButtonCallback(GLFWwindow* window, int button, int action, int mode) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->controller.handleMouseClickInput(button, action, mode);
    }
    printf("button_callback [%d,%d,%d]\n", button, action, mode);
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

float Application::randomFloat(double min, double max) {

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

void Application::updateWindowSizeInScenes(int width, int height) {
    for (std::shared_ptr<Scene> sc : scenes) {
        sc->camera->setWindowSize(width, height);
    }
}

void Application::rotateCamera(float xOffset, float yOffset) {
    scenes[currentSceneNumber]->camera->setOrientation(scenes[currentSceneNumber]->camera->getAlpha() - yOffset, scenes[currentSceneNumber]->camera->getFi() + xOffset);
}

void Application::lockCursor(bool lock) {
    if (lock) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Lock cursor on app window
    }
    else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Unlock cursor
    }
}

std::shared_ptr<Scene> Application::getCurrentScene() {
	return scenes[currentSceneNumber];
}


