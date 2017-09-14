#ifndef SHADER_H
#define SHADER_H

#if defined(TARGET_PLATFORM_WINDOWS) || defined(WIN32)
#include <glad/glad.h>
#endif 

#if defined(TARGET_PLATFORM_MAC) || defined(TARGET_PLATFORM_IOS)
#include <OpenGL/GL3.h>
#endif 

#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <map>


namespace Managers {


	class ShaderManager
	{

	public:
		ShaderManager();
		~ShaderManager();
		 void CreateProgram(const std::string& shaderName, 
							const std::string& vertexShaderFileName,
							const std::string& fragmentShaderFileName);
		 static const GLuint GetShader(const std::string& shaderName);

	private:
		std::string ReadShader(const std::string& shaderFileName);
		GLuint CreateShader(GLuint shaderType, 
							const std::string& shaderSource,
							const std::string& shaderName);
		
		static std::map<std::string, GLuint> programs;

	};
}
#endif
