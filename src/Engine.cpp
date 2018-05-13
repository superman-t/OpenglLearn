#include "Engine.h"

#include <fstream>
#include <iostream>

using namespace BasicEngine;
using namespace Init;
using namespace Managers;

#define SafeDelete( ptr ) if( (ptr) != NULL ) { delete (ptr); (ptr) = NULL; }

Engine::Engine()
:mWindowInfo(std::string("OpenGL Basic Engine"),
		1280, 720,//size
		400, 200, //position
		true)//reshape
,mContextInfo(3.0, 3.0, true)
,mFrameBufferInfo(true, true, true, true)

{
	Init();
}

Engine::~Engine()
{
	SafeDelete(mModelsManager)
	SafeDelete(mSceneManager)

	glfwTerminate();
}

bool Engine::Init()
{
	InitGlfw::Init(mWindowInfo, mContextInfo, mFrameBufferInfo);

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
