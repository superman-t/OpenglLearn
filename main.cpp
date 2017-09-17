//
//  main.cpp
//  OpenglLearn
//
//  Created by AceTian on 2017/9/6.
//  Copyright (c) 2017 AceTian. All rights reserved.
//

#include "src/Init/InitGlfw.h"

#include <iostream>
#include <cmath>
#include "src/Managers/SceneManager.h"
#include "src/Managers/ShaderManager.h"
#include "src/Init/IListener.h"

using namespace Init;
using namespace Managers;

int main(int argc, const char * argv[]) {
	WindowInfo window(std::string("OpenGL Learn Tutorial "),
		800, 600,//size
		400, 200, //position
		true);//reshape
	ContextInfo context(3, 3, true);
	FrameBufferInfo frameBufferInfo(true, true, true, true);
	InitGlfw::Init(window, context, frameBufferInfo);

        
	IListener* scene = new SceneManager();

	InitGlfw::SetListener(scene);
	InitGlfw::SetPolygonMode(GL_FILL);
	InitGlfw::Run();
	
    glfwTerminate();
    return 0;
}



