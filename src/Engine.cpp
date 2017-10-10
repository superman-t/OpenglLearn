#include "Engine.h"


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
	if (mShaderManager)
		delete mShaderManager;
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
	
	mShaderManager = new ShaderManager();
#ifdef TARGET_COMPILE_XCODE
	mShaderManager->CreateProgram("PlaneShader", "../../Shaders/plane.vs", "../../Shaders/plane.fs");
    mShaderManager->CreateProgram("CubeShader", "../../Shaders/cube.vs", "../../Shaders/cube.fs");
#else
	mShaderManager->CreateProgram("PlaneShader", "../Shaders/plane.vs", "../Shaders/plane.fs");
    mShaderManager->CreateProgram("CubeShader", "../Shaders/cube.vs", "../Shaders/cube.fs");
#endif

	if (mShaderManager)
	{
		mModelsManager = new ModelsManager();
		mSceneManager->SetModelsManager(mModelsManager);
	}
	else
	{
		return false;
	}

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

ShaderManager* Engine::GetShaderManager() const
{
	return mShaderManager;
}

ModelsManager* Engine::GetModelsManager() const
{
	return mModelsManager;
}
