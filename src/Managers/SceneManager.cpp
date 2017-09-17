#include "SceneManager.h"
using namespace Managers;

SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    
    mShaderManager = new ShaderManager();
#ifdef TARGET_COMPILE_XCODE
    mShaderManager->CreateProgram("ColorShader", "../../Shaders/shader.vs", "../../Shaders/shader.fs");
#else
    mShaderManager->CreateProgram("ColorShader", "../Shaders/shader.vs", "../Shaders/shader.fs");
#endif

    viewMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, -1.0f, 0.0f,
                            0.0f, 0.0f, 10.0f, 1.0f);
    
    float ar = (float)800/600;
    float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;
    
    projectionMatrix[0][0] = 1.0f / (ar * tan(angle / 2.0f));
    projectionMatrix[1][1] = 1.0f / tan(angle / 2.0f);
    projectionMatrix[2][2] = (-near1 - far1) / (near1 - far1);
    projectionMatrix[2][3] = 1.0f;
    projectionMatrix[3][2] = 2.0f * near1 * far1 / (near1 - far1);
    
    mModelsManager = new ModelsManager();
}

SceneManager::~SceneManager()
{
	delete mShaderManager;
    delete mModelsManager;
}

void SceneManager::NotifyBeginFrame()
{
    mModelsManager->Update();
}

void SceneManager::NotifyRenderFrame()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//状态设置函数
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//状态应用函数
    
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    mModelsManager->Draw();
    mModelsManager->Draw(projectionMatrix, viewMatrix);

}

void SceneManager::NotifyEndFrame()
{

}

void SceneManager::NotifyReshape(int width, int height, int previousWidth, int previousHeight)
{
    float ar = (float)width/height;
    float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;
    
    projectionMatrix[0][0] = 1.0f / (ar * tan(angle / 2.0f));
    projectionMatrix[1][1] = 1.0f / tan(angle / 2.0f);
    projectionMatrix[2][2] = (-near1 - far1) / (near1 - far1);
    projectionMatrix[2][3] = 1.0f;
    projectionMatrix[3][2] = 2.0f * near1 * far1 / (near1 - far1);
}

void SceneManager::SetModelsManager(Managers::ModelsManager*& modelsManager)
{
    mModelsManager = modelsManager;
}
