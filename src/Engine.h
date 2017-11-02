#ifndef Engine_h
#define Engine_h

#include "Init/InitGlfw.h"
#include "Managers/SceneManager.h"
#include "Managers/ModelsManager.h"
namespace BasicEngine
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		bool Init();
		void Run();
		Managers::SceneManager* GetSceneManager() const;
		Managers::ModelsManager* GetModelsManager() const;

	
	private:
		Managers::SceneManager* mSceneManager;
		Managers::ModelsManager* mModelsManager;

	};
}
#endif