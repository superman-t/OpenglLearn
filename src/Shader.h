#ifndef SHADER_H
#define SHADER_H

#if defined(TARGET_PLATFORM_WINDOWS) || defined(WIN32)
#include <glad/glad.h>
#endif // TARGET_PLATFORM_WINDOWS || WIN32

#if defined(TARGET_PLATFORM_MAC) || defined(TARGET_PLATFORM_IOS)
#include <OpenGL/GL3.h>
#endif // TARGET_PLATFORM_MAC || TARGET_PLATFORM_IOS

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include "GLFW/glfw3.h"

class Shader
{
    
public:
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    void Use();

private:
    GLuint Program;
	std::string ReadShader(const GLchar* shaderPath);
	GLuint CreateShader(GLuint shaderType, const GLchar* shaderSource);
	GLuint CreateProgram(GLuint vs, GLuint fs);

    
};

std::string Shader::ReadShader(const GLchar* shaderPath)
{
	std::string shaderCode;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;

		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	//std::cout << shaderCode << std::endl;
	return shaderCode;
}

GLuint Shader::CreateShader(GLuint shaderType, const GLchar* shaderSource)
{
	GLuint shader;
	//std::cout << shaderSource << std::endl;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

GLuint Shader::CreateProgram(GLuint vs, GLuint fs)
{
	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vsource = ReadShader(vertexPath);
	const GLchar* vShaderCode = vsource.c_str();
	std::string fsource = ReadShader(fragmentPath);
    const GLchar* fShaderCode = fsource.c_str();
	std::cout << fShaderCode << std::endl;
	GLuint vs = CreateShader(GL_VERTEX_SHADER, vShaderCode);
	GLuint fs = CreateShader(GL_FRAGMENT_SHADER, fShaderCode);

	this->Program = CreateProgram(vs, fs);
}

void Shader::Use()
{
    glUseProgram(this->Program);
}

#endif
