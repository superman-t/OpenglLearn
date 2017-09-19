#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "ShaderManager.h"
#include "ModelsManager.h"
#include "../Init/IListener.h"


namespace Managers
{
	class SceneManager : public IListener
	{
	public:
		SceneManager();
		~SceneManager();

		virtual void NotifyBeginFrame();
		virtual void NotifyRenderFrame();
		virtual void NotifyEndFrame();
		virtual void NotifyReshape(int width, int height, int previousWidth, int previousHeight);
        
        void SetModelsManager(Managers::ModelsManager*& modelsManager);

	private:
		ShaderManager* mShaderManager;
        ModelsManager* mModelsManager;
        
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
	};
}

#endif
