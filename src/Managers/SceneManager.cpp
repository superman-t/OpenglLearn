#include "SceneManager.h"
#include <glm/gtc/functions.hpp>
using namespace Managers;

SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    
    mCamera = new Camera(
		glm::vec3(0, 150, 450),//pos                         
		glm::vec3(0, 1, 0)); //up
    
    viewMatrix = mCamera->GetViewMatrix();
    projectionMatrix = glm::perspective(glm::radians(mCamera->zoom), (float)800/600, 0.1f, 1000.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0, 1.0, 0.0));
	mouseRightButtonPressed = false;
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
    viewMatrix = mCamera->GetViewMatrix();
    projectionMatrix = glm::perspective(glm::radians(mCamera->zoom), (float)800/600, 0.1f, 2000.0f);
	modelMatrix = glm::rotate(modelMatrix, .005f, glm::vec3(0, 1, 0));

	mCamera->ProcessKeyboard(cameraDirection, deltaTime);
	mModelsManager->Update();
}

void SceneManager::NotifyRenderFrame(GLfloat deltaTime)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//状态设置函数
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//状态应用函数
    
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    mModelsManager->Draw();
    mModelsManager->Draw(projectionMatrix, viewMatrix, modelMatrix);

}

void SceneManager::NotifyEndFrame(GLfloat deltaTime)
{

}

void SceneManager::NotifyReshape(int width, int height, int previousWidth, int previousHeight)
{
	projectionMatrix = glm::perspective(glm::radians(mCamera->zoom), (float)width / height, 0.1f, 2000.0f);
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
	mCamera->ProcessMouseMovement(xpos - lastXpos, -ypos + lastYpos, true);
	lastXpos = xpos;
	lastYpos = ypos;
}

void SceneManager::NotifyMouseButtonInput(int button, int action, int mods, double xpos, double ypos)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		mouseRightButtonPressed = true;
		lastXpos = xpos;
		lastYpos = ypos;
		std::cout << "mouse right button pressed " << xpos << " " << ypos << std::endl;
	}
	else
	{
		mouseRightButtonPressed = false;
	}
		
}

void SceneManager::NotifyScrollMove(double xoffset, double yoffset)
{
    mCamera->ProcessMouseScroll(yoffset);
}



