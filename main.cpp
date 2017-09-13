//
//  main.cpp
//  OpenglLearn
//
//  Created by AceTian on 2017/9/6.
//  Copyright (c) 2017 AceTian. All rights reserved.
//

#if defined(TARGET_PLATFORM_WINDOWS) || defined(WIN32)
#include <glad/glad.h>
#endif // TARGET_PLATFORM_WINDOWS || WIN32

#if defined(TARGET_PLATFORM_MAC) || defined(TARGET_PLATFORM_IOS)
#include <OpenGL/GL3.h>
#endif // TARGET_PLATFORM_MAC || TARGET_PLATFORM_IOS


#include <GLFW/glfw3.h>
#include "3rdparty/glm/glm.hpp"
#include "3rdparty/glm/gtc/matrix_transform.hpp"
#include "3rdparty/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <cmath>
#include "src/Shader.h"
#include "src/GameModels.h"

Models::GameModels* gameModels;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

int InitWindows()
{

#if defined(TARGET_PLATFORM_WINDOWS) || defined(WIN32)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
#endif

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef TARGET_PLATFORM_MAC
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    
    return 0;
}



int main(int argc, const char * argv[]) {
    // insert code here...
    InitWindows();
    gameModels = new Models::GameModels();
    gameModels->CreateTriangleModel("triangle1");
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGLLearn", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    std::cout << vec.x;
    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);   
    
// 着色器
#ifdef TARGET_COMPILE_XCODE
    Shader outShader("../../Shaders/shader.vs", "../../Shaders/shader.fs");
#else
    Shader outShader("../Shaders/shader.vs", "../Shaders/shader.fs");
#endif
    
    GLint numAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttributes);
    std::cout << "Max vertex attrigs supported:" << numAttributes << std::endl;

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
       
    
        // Render
        // Clear the colorbuffer
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    
        
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);  
    
  
        glBindVertexArray(gameModels->GetModel("triangle1"));
        outShader.Use();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        // Swap the screen buffers
        glfwSwapBuffers(window);

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
    }
    
    
       // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    delete gameModels;
    return 0;
}
// Is called whenever a key is pressed/released via GLFW
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
