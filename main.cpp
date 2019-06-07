//
//  main.cpp
//  OpenglLearn
//
//  Created by AceTian on 2017/9/6.
//  Copyright (c) 2017 AceTian. All rights reserved.
//

#include "src/Init/InitGlfw.h"
#include "src/Rendering/Models/Cube.h"
#include "src/Rendering/Models/CubeIndexed.h"
#include "src/Rendering/Models/Model.h"
#include "src/Rendering/Label.h"

#include "src/Engine.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include "src/Managers/ShaderManager.h"

using namespace std;
using namespace BasicEngine;
using namespace Rendering;
using namespace Models;
using namespace Managers;

int main(int argc, const char * argv[]) {
	Engine* engine = new Engine();

	WindowInfo windowInfo = engine->GetWindowInfo();
	float width = windowInfo.width;
	float height = windowInfo.height;

	CubeIndexed* cube = new CubeIndexed();
	cube->SetProgram( ShaderManager::getInstance()->GetShader( "cube" ) );
	cube->Create();

    Model* model1 = new Model(std::string(string(ROOTPATH) + "res/crystal_maiden/crystal_maiden_econ.fbx"));
	model1->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	model1->SetProgram(ShaderManager::getInstance()->GetShader("texture"));

	
	engine->GetModelsManager()->AddModel("cube", cube);
	engine->GetModelsManager()->AddModel("model", model1);
	engine->Run();

	delete engine;
    return 0;
}



