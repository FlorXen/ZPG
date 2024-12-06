#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <string>
#include <iostream>

#include <SOIL.h>

#include <glm/vec4.hpp> // glm::vec4

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structures
#include<assimp/postprocess.h>// Post processingflags

#include "Model.h"

struct Vertex
{
    float Position[3];
    float Normal[3];
    float Texture[2];
    float Tangent[3];
};

class AssimpModel : public MyApp::Model
{
public:
    AssimpModel(std::string fileName);
};

