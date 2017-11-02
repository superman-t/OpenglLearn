#include "Engine.h"

#include <fstream>
#include <iostream>

using namespace BasicEngine;
using namespace Init;
using namespace Managers;

Engine::Engine()
{
	Init();
}

Engine::~Engine()
{
	if (mModelsManager)
		delete mModelsManager;
	if (mSceneManager)
		delete mSceneManager;
	
	glfwTerminate();
}

bool Engine::Init()
{
	WindowInfo window(std::string("OpenGL Basic Engine"),
		800, 600,//size
		400, 200, //position
		true);//reshape
	ContextInfo context(3, 3, true);
	FrameBufferInfo frameBufferInfo(true, true, true, true);
	InitGlfw::Init(window, context, frameBufferInfo);

	mSceneManager = new SceneManager();
	if (mSceneManager)
	{
		InitGlfw::SetListener(mSceneManager);
		InitGlfw::SetPolygonMode(GL_FILL);
	}
	else
	{
		return false;
	}
	
	mModelsManager = new ModelsManager();
	mSceneManager->SetModelsManager(mModelsManager);
	
	return true;
}

void Engine::Run()
{
	InitGlfw::Run();
}

SceneManager* Engine::GetSceneManager() const
{
	return mSceneManager;
}

ModelsManager* Engine::GetModelsManager() const
{
	return mModelsManager;
}
