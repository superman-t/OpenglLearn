//
//  main.cpp
//  OpenglLearn
//
//  Created by AceTian on 2017/9/6.
//  Copyright (c) 2017 AceTian. All rights reserved.
//

#ifdef TARGET_PLATFORM_WINDOWS || WIN32
#include <glad/glad.h>
#endif // TARGET_PLATFORM_WINDOWS || WIN32

#ifdef TARGET_PLATFORM_MAC || TARGET_PLATFORM_IOS
#include <OpenGL/GL3.h>
#endif // TARGET_PLATFORM_MAC



#include "GLFW/glfw3.h"
#include <iostream>
#include <cmath>
#include "src/Shader.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int main(int argc, const char * argv[]) {
    // insert code here...
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef TARGET_PLATFORM_MAC
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGLLearn", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

#ifdef TARGET_PLATFORM_WINDOWS || WIN32
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
#endif
	

// 着色器
    Shader outShader("../src/shader.vs", "../src/shader.fs");
    
//顶点数据
    GLfloat vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 右上角
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 右下角
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,// 左下角
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,// 左上角
    };
    
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // 绑定顶点数组
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);//layout = 0
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));//layout = 1
    glEnableVertexAttribArray(1);
    //解绑vbo
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //解绑ebo
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //解绑vao
    glBindVertexArray(0);
    
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
    
        //GLfloat timeValue = glfwGetTime();
        //GLfloat greenValue = (sin(timeValue)/2) + 0.5;
        //GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "outColor");
        outShader.Use();
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);  
    
  
        glBindVertexArray(VAO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    
        // Swap the screen buffers
        glfwSwapBuffers(window);

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
    }
    
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
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