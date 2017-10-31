#ifndef InitGlfw_H
#define InitGlfw_H

#include "../GLHealder.h"

#include "WindowInfo.h"
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "IListener.h"

namespace Init {
	typedef void(*RenderCallback)();
	class InitGlfw
	{
		
	public:
		static void Init(
			const WindowInfo& windowInfo,
			const ContextInfo& contextInfo,
			const FrameBufferInfo& frameInfo);
		static void Run();
		static void SetRenderCallback(RenderCallback pFunc);
		static void SetPolygonMode(GLenum mode);
		static void SetListener(IListener* listener);

	private:
		static GLFWwindow* mWindowHandler;
		static RenderCallback mRenderCallback;
		static GLenum mPolygonMode;
        
        static GLfloat currentFrame;
        static GLfloat deltaTime;
        static GLfloat lastFrame;

		static IListener* mListener;
		static WindowInfo mWindowInfo;

	private:
		static void Render(GLfloat deltaTime);
        static void CalculateDeltaTime();
		static void Close(int value);
		static void CloseCallback(GLFWwindow* window);
		static void FrameSizeChangeCallback(GLFWwindow* window, int width, int height);
        static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void KeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void PrintOpenglInfo(const WindowInfo& winndowInfo, const ContextInfo& contextInfo);
		static void DisplayCallback(GLfloat deltaTime);
		static void SetOpenglModes();
	};
}

#endif
