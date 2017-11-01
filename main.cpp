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

#include "src/Engine.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SOIL.h>
#include <string>


using namespace BasicEngine;
using namespace Rendering;
using namespace Models;
int main(int argc, const char * argv[]) {
	Engine* engine = new Engine();

	CubeIndexed* cube = new CubeIndexed();
	cube->SetProgram(engine->GetShaderManager()->GetShader("cube"));
	cube->Create();
    
	Model* model = new Model(std::string("../res/suzanne.obj"));
	model->SetProgram(engine->GetShaderManager()->GetShader("cube"));
    
	engine->GetModelsManager()->AddModel("cube", cube);
	engine->GetModelsManager()->AddModel("model", model);
	engine->Run();

	delete engine;
    return 0;
}



