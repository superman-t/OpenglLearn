//
//  main.cpp
//  OpenglLearn
//
//  Created by AceTian on 2017/9/6.
//  Copyright (c) 2017 AceTian. All rights reserved.
//

#include "src/Init/InitGlfw.h"
#include "3rdparty/glm/glm.hpp"
#include "3rdparty/glm/gtc/matrix_transform.hpp"
#include "3rdparty/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <cmath>
#include "src/Managers/ShaderManager.h"
#include "src/Managers/GameModels.h"

using namespace Init;

Models::GameModels* gameModels;
Managers::ShaderManager* shaderManager;

void rc()
{
	glBindVertexArray(gameModels->GetModel("triangle1"));
	glUseProgram(shaderManager->GetShader("triangle1"));
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(int argc, const char * argv[]) {
	WindowInfo window(std::string("OpenGL Learn Tutorial "),
		800, 600,//size
		400, 200, //position
		true);//reshape

	ContextInfo context(3, 3, true);
	FrameBufferInfo frameBufferInfo(true, true, true, true);
	InitGlfw::Init(window, context, frameBufferInfo);

    gameModels = new Models::GameModels();
	shaderManager = new Managers::ShaderManager();

// 着色器
#ifdef TARGET_COMPILE_XCODE
	shaderManager->CreateProgram("triangle1", "../../Shaders/shader.vs", "../../Shaders/shader.fs");
#else
    shaderManager->CreateProgram("triangle1", "../Shaders/shader.vs", "../Shaders/shader.fs");
#endif
    
	
	gameModels->CreateTriangleModel("triangle1");

	InitGlfw::SetRenderCallback(rc);
	InitGlfw::SetPolygonMode(GL_FILL);
	InitGlfw::Run();
	

    glfwTerminate();
    delete gameModels;
	delete shaderManager;
    return 0;
}



