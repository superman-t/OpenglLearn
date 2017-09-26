#include "SceneManager.h"
using namespace Managers;

SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    
    mCamera = new Camera();
    
    viewMatrix = mCamera->GetViewMatrix();
    projectionMatrix = glm::perspective(mCamera->zoom, (float)800/600, 0.1f, 2000.0f);
    lastXpos = 400;
    lastYpos = 300;
    
    cameraDirection = UNKNOW;
	
}

SceneManager::~SceneManager()
{
    delete mCamera;
}

void SceneManager::NotifyBeginFrame(GLfloat deltaTime)
{
    mModelsManager->Update();
    mCamera->ProcessKeyboard(cameraDirection, deltaTime);
    viewMatrix = mCamera->GetViewMatrix();
    projectionMatrix = glm::perspective(mCamera->zoom, (float)800/600, 0.1f, 2000.0f);
    
}

void SceneManager::NotifyRenderFrame(GLfloat deltaTime)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//状态设置函数
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//状态应用函数
    
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    mModelsManager->Draw();
    mModelsManager->Draw(projectionMatrix, viewMatrix);

}

void SceneManager::NotifyEndFrame(GLfloat deltaTime)
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

void SceneManager::NotifyKeyInput(int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_A && action == GLFW_PRESS){
        cameraDirection = LEFT;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        cameraDirection = BACKWARD;
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        cameraDirection = FORWARD;
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        cameraDirection = RIGHT;
    if (action == GLFW_RELEASE)
    {
        cameraDirection = UNKNOW;
    }
}

void SceneManager::NotifyMouseMove(double xpos, double ypos)
{
    mCamera->ProcessMouseMovement(xpos - lastXpos, lastYpos - ypos, true);
    lastXpos = xpos;
    lastYpos = ypos;
}


void SceneManager::NotifyScrollMove(double xoffset, double yoffset)
{
    mCamera->ProcessMouseScroll(yoffset);
}



