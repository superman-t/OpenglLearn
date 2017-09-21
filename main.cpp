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


#include "src/Engine.h"
using namespace BasicEngine;
using namespace Rendering;
using namespace Models;
int main(int argc, const char * argv[]) {
	Engine* engine = new Engine();

	CubeIndexed* cube = new CubeIndexed();
	cube->SetProgram(engine->GetShaderManager()->GetShader("ColorShader"));
	cube->Create();

	engine->GetModelsManager()->SetModel("cube", cube);
	engine->Run();

	delete engine;
    return 0;
}



