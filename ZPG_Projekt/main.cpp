/*
* Projekt do předmětu ZPG
* 
* Autor: Filip Hort
* Login: Hor0552
*/

#include "Application.h"

int main(void)
{
    Application* app = new Application();
    
    app->Initialize();
    
    app->CreateScenes();

    app->Run();

}