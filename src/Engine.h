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
		const WindowInfo& GetWindowInfo(void) const;
		const ContextInfo& GetContextInfo(void) const;
		const FrameBufferInfo& GetFrameBufferInfo(void) const;

	protected:
		WindowInfo mWindowInfo;
		ContextInfo mContextInfo;
		FrameBufferInfo mFrameBufferInfo;
	private:
		Managers::SceneManager* mSceneManager;
		Managers::ModelsManager* mModelsManager;

	};

	inline const WindowInfo& Engine::GetWindowInfo(void) const
	{
		return mWindowInfo;
	}

	inline const ContextInfo& Engine::GetContextInfo(void) const
	{
		return mContextInfo;
	}

	inline const FrameBufferInfo& Engine::GetFrameBufferInfo(void) const
	{
		return mFrameBufferInfo;
	}



}
#endif