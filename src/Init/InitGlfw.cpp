#include "InitGlad.h"
#include "InitGlfw.h"

#include <iostream>
using namespace Init;

GLFWwindow* InitGlfw::mWindowHandler;
RenderCallback InitGlfw::mRenderCallback;
GLenum InitGlfw::mPolygonMode;

GLfloat InitGlfw::currentFrame;
GLfloat InitGlfw::deltaTime;
GLfloat InitGlfw::lastFrame;

IListener* InitGlfw::mListener;
WindowInfo InitGlfw::mWindowInfo;

void InitGlfw::Init(const WindowInfo& windowInfo, const ContextInfo& contextInfo, const FrameBufferInfo& frameInfo)
{
	glfwInit();
	if (contextInfo.core) 
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextInfo.major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextInfo.minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	else
	{
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	}

#ifdef TARGET_PLATFORM_MAC
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	GLFWwindow* window = glfwCreateWindow(windowInfo.width, windowInfo.height, windowInfo.name.c_str(), nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	std::cout << "GLFW:Initialized" << std::endl;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, KeyInputCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetFramebufferSizeCallback(window, FrameSizeChangeCallback);
	glfwSetWindowCloseCallback(window, CloseCallback);

	glfwSetWindowPos(window, windowInfo.posx, windowInfo.posy);
	glfwMakeContextCurrent(window);

#if defined(TARGET_PLATFORM_WINDOWS) || defined(WIN32)
	InitGlad::Init();
#endif 

	PrintOpenglInfo(windowInfo, contextInfo);
	
	mWindowHandler = window;
	mWindowInfo = windowInfo;
    deltaTime = 1.0f/60;
}

void InitGlfw::Run()
{
	if (mWindowHandler == nullptr)
	{
		std::cout << "Failed to run, windowHandler is null" << std::endl;
	}
	glPolygonMode(GL_FRONT_AND_BACK, mPolygonMode);
	while(!glfwWindowShouldClose(mWindowHandler))
	{
		glfwPollEvents();
		Render(deltaTime);
        CalculateDeltaTime();
	}
}

void InitGlfw::CalculateDeltaTime()
{
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void InitGlfw::SetRenderCallback(RenderCallback pFunc)
{
	mRenderCallback = pFunc;
}

void InitGlfw::SetPolygonMode(GLenum mode)
{
	mPolygonMode = mode;
}

void InitGlfw::SetListener(IListener* listener)
{
	mListener = listener;
}

void InitGlfw::Close(int value)
{
	glfwSetWindowShouldClose(mWindowHandler, value);
}

void InitGlfw::Render(GLfloat deltaTime)
{
	if (mRenderCallback != nullptr) {
		mRenderCallback();
		glfwSwapBuffers(mWindowHandler);
	}
	else 
	{
		DisplayCallback(deltaTime);
	}
}

void InitGlfw::FrameSizeChangeCallback(GLFWwindow* window, int width, int height)
{
	if (mWindowInfo.isReshapble)
	{
		if (mListener)
		{
			mListener->NotifyReshape(width, height, mWindowInfo.width, mWindowInfo.height);
			mWindowInfo.width = width;
			mWindowInfo.height = height;
		}

		glViewport(0, 0, width, height);
	}
	
}

void InitGlfw::CloseCallback(GLFWwindow* window)
{
	std::cout << "CloseCallback" << std::endl;
}

void InitGlfw::KeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//std::cout << "Key Input: " << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		Close(GL_TRUE);
    if (mListener)
    {
        mListener->NotifyKeyInput(key, scancode, action, mode);
    }
}

void InitGlfw::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    //std::cout << "mouse " << xpos << " " << ypos << std::endl;
    if (mListener)
    {
        mListener->NotifyMouseMove(xpos, ypos);
    }
}

void InitGlfw::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    std::cout << "scroll " << xoffset << ":" << yoffset << std::endl;
    if (mListener)
    {
        mListener->NotifyScrollMove(xoffset, yoffset);
    }
}

void InitGlfw::PrintOpenglInfo(const WindowInfo& windowInfo, const ContextInfo& contextInfo)
{
	unsigned char* render = (unsigned char*)glGetString(GL_RENDERER);
	unsigned char* vender = (unsigned char*)glGetString(GL_VENDOR);
	unsigned char* version = (unsigned char*)glGetString(GL_VERSION);

	std::cout << "**************************************************" << std::endl;
	std::cout << "GLFW:Initialize" << std::endl;
	std::cout << "GLFW:\tVender: " << vender << std::endl;
	std::cout << "GLFW:\tRender: " << render << std::endl;
	std::cout << "GLFW:\tOpengl Version: " << version << std::endl;
	std::cout << "**************************************************" << std::endl;
}

void InitGlfw::DisplayCallback(GLfloat deltaTime)
{
    //std::cout << "DisplayCallback" << std::endl;
	if (mListener)
	{
		mListener->NotifyBeginFrame(deltaTime);
		mListener->NotifyRenderFrame(deltaTime);

		glfwSwapBuffers(mWindowHandler);
		
		mListener->NotifyEndFrame(deltaTime);
	}
}
