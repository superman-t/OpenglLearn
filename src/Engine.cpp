#include "Engine.h"

#include <fstream>
#include <iostream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

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
	std::string shaderPath("../../Shaders");
#else
	std::string shaderPath("../Shaders");
#endif
	std::string filename, path;
	for (fs::recursive_directory_iterator p(shaderPath); p != fs::recursive_directory_iterator{}; ++p)
	{
		filename = p->path().string();
		int start = filename.find_last_of('\\');
		int end = filename.find_last_of(".");
		path = filename.substr(0, start);
		filename = filename.substr(start + 1, end - 1 - start);
		mShaderManager->CreateProgram(filename, path + "/" + filename + ".vs", path + "/" + filename + ".fs");
	}

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
