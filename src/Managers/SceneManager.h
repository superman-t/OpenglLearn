#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "ShaderManager.h"
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

	private:
		ShaderManager* mShaderManager;
	};
}

#endif