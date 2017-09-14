//
//  main.cpp
//  OpenglLearn
//
//  Created by AceTian on 2017/9/6.
//  Copyright (c) 2017 AceTian. All rights reserved.
//

#if defined(TARGET_PLATFORM_WINDOWS) || defined(WIN32)
#include <glad/glad.h>
#endif 

#if defined(TARGET_PLATFORM_MAC) || defined(TARGET_PLATFORM_IOS)
#include <OpenGL/GL3.h>
#endif

#include <GLFW/glfw3.h>
#include "3rdparty/glm/glm.hpp"
#include "3rdparty/glm/gtc/matrix_transform.hpp"
#include "3rdparty/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <cmath>
#include "src/Managers/ShaderManager.h"
#include "src/Managers/GameModels.h"

Models::GameModels* gameModels;
Managers::ShaderManager* shaderManager;
// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

GLFWwindow* InitWindows()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef TARGET_PLATFORM_MAC
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGLLearn", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	
	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
#if defined(TARGET_PLATFORM_WINDOWS) || defined(WIN32)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}
#endif
    return window;
}

int main(int argc, const char * argv[]) {
	GLFWwindow* window = InitWindows();

    gameModels = new Models::GameModels();
	shaderManager = new Managers::ShaderManager();
// 着色器
#ifdef TARGET_COMPILE_XCODE
	shaderManager->CreateProgram("triangle1", "../../Shaders/shader.vs", "../../Shaders/shader.fs");
#else
    shaderManager->CreateProgram("triangle1", "../Shaders/shader.vs", "../Shaders/shader.fs");
#endif
    
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	gameModels->CreateTriangleModel("triangle1");
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    
        glBindVertexArray(gameModels->GetModel("triangle1"));
		glUseProgram(shaderManager->GetShader("triangle1"));
        glDrawArrays(GL_TRIANGLES, 0, 3);
      
        glfwSwapBuffers(window);
		glfwPollEvents();
    }
    
    glfwTerminate();
    delete gameModels;
	delete shaderManager;
    return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
