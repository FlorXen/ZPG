#include "Application.h"

int main(void)
{
    Application* app = new Application();

    app->Initialize();

    app->CreateScenes();

    app->Run();

}

