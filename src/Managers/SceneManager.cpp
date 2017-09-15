#include "SceneManager.h"
using namespace Managers;

SceneManager::SceneManager()
{
	mShaderManager = new ShaderManager();

	glEnable(GL_DEPTH_TEST);

	// 着色器
#ifdef TARGET_COMPILE_XCODE
	mShaderManager->CreateProgram("ColorShader", "../../Shaders/shader.vs", "../../Shaders/shader.fs");
#else
	mShaderManager->CreateProgram("ColorShader", "../Shaders/shader.vs", "../Shaders/shader.fs");
#endif
}

SceneManager::~SceneManager()
{
	delete mShaderManager;
}

void SceneManager::NotifyBeginFrame()
{

}

void SceneManager::NotifyRenderFrame()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//状态设置函数
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//状态应用函数


}

void SceneManager::NotifyEndFrame()
{

}

void SceneManager::NotifyReshape(int width, int height, int previousWidth, int previousHeight)
{

}

