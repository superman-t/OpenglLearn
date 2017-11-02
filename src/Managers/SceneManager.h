#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "ShaderManager.h"
#include "ModelsManager.h"
#include "../Camera.h"
#include "../Init/IListener.h"
#include "../Rendering/Label.h"


namespace Managers
{
	class SceneManager : public IListener
	{
	public:
		SceneManager();
		~SceneManager();

		virtual void NotifyBeginFrame(GLfloat deltaTime);
		virtual void NotifyRenderFrame(GLfloat deltaTime);
		virtual void NotifyEndFrame(GLfloat deltaTime);
		virtual void NotifyReshape(int width, int height, int previousWidth, int previousHeight);
        
        virtual void NotifyKeyInput(int key, int scancode, int action, int mode);
        virtual void NotifyMouseMove(double xpos, double ypos);
		virtual void NotifyMouseButtonInput(int button, int action, int mods, double xpos, double ypos);
        virtual void NotifyScrollMove(double xoffset, double yoffset);
        
        void SetModelsManager(Managers::ModelsManager* modelsManager);

	private:
		ShaderManager* mShaderManager;
        ModelsManager* mModelsManager;
        Camera* mCamera;
		Label* fpsLabel;
        
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
		glm::mat4 modelMatrix;
        
        CameraMovement cameraDirection;
        GLfloat lastXpos, lastYpos;
		bool mouseRightButtonPressed;
		bool mouseLeftButtonPressed;
		GLfloat fpsInterval;
	};
}

#endif
