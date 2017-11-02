#include "SceneManager.h"
#include <glm/gtc/functions.hpp>
using namespace Managers;

SceneManager::SceneManager()
{
    mCamera = new Camera(
		glm::vec3(0, 150, 450),//pos                         
		glm::vec3(0, 1, 0)); //up
    
    viewMatrix = mCamera->GetViewMatrix();
    projectionMatrix = glm::perspective(glm::radians(mCamera->zoom), (float)800/600, 0.1f, 1000.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0, 1.0, 0.0));
	//modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1));
	mouseRightButtonPressed = false;
	mouseLeftButtonPressed = false;
	fpsInterval = 1 / 60.0;
    lastXpos = 400;
    lastYpos = 300;
    
    cameraDirection = UNKNOW;
	fpsLabel = new Label(std::string("60.0"), 20, glm::vec2(30, 100));
	fpsLabel->SetProgram(ShaderManager::getInstance()->GetShader("text"));
}

SceneManager::~SceneManager()
{
    delete mCamera;
}

void SceneManager::NotifyBeginFrame(GLfloat deltaTime)
{
    viewMatrix = mCamera->GetViewMatrix();
    projectionMatrix = glm::perspective(glm::radians(mCamera->zoom), (float)800/600, 0.1f, 2000.0f);
	//modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0, 0.5, 0.0));
	
	//modelMatrix = glm::rotate(modelMatrix, .005f, glm::vec3(0, 1, 0));

	mCamera->ProcessKeyboard(cameraDirection, deltaTime);
	mModelsManager->Update();
	fpsInterval -= deltaTime;

	if (fpsInterval < 0.0) {
		fpsInterval = 1 / 60.0;
		char text[256];
		sprintf(text, "fps: %.1f", 1.0 / deltaTime);
		fpsLabel->SetString(std::string(text));
	}
	
}

void SceneManager::NotifyRenderFrame(GLfloat deltaTime)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//״̬���ú���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//״̬Ӧ�ú���
    
    
    mModelsManager->Draw(projectionMatrix, viewMatrix, modelMatrix);
	mModelsManager->Draw();
}

void SceneManager::NotifyEndFrame(GLfloat deltaTime)
{

}

void SceneManager::NotifyReshape(int width, int height, int previousWidth, int previousHeight)
{
	projectionMatrix = glm::perspective(glm::radians(mCamera->zoom), (float)width / height, 0.1f, 2000.0f);
}

void SceneManager::SetModelsManager(Managers::ModelsManager* modelsManager)
{
    mModelsManager = modelsManager;
	mModelsManager->AddModelNDC("fpsLabel", fpsLabel);
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
	if (mouseRightButtonPressed)
	{
		modelMatrix = glm::rotate(modelMatrix, (float)(xpos - lastXpos)/180, glm::vec3(0, 1, 0));
	}
	if (mouseLeftButtonPressed)
		mCamera->ProcessMouseMovement(0, -ypos + lastYpos, true);
	
	
	lastXpos = xpos;
	lastYpos = ypos;
}

void SceneManager::NotifyMouseButtonInput(int button, int action, int mods, double xpos, double ypos)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		mouseRightButtonPressed = true;
	}
	else
	{
		mouseRightButtonPressed = false;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		mouseLeftButtonPressed = true;
	}
	else
	{
		mouseLeftButtonPressed = false;
	}

	lastXpos = xpos;
	lastYpos = ypos;
		
}

void SceneManager::NotifyScrollMove(double xoffset, double yoffset)
{
    mCamera->ProcessMouseScroll(yoffset);
}



