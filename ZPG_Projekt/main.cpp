#include "Application.h"

int main(void)
{
    Application* app = new Application();

    app->Initialize();

    app->CreateShaders();
    app->CreateModels();
    app->Run();

}

