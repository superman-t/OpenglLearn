#ifndef ShaderManager_H
#define ShaderManager_H

#include "../GLHealder.h"

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
		static ShaderManager* getInstance();
	private:
		void Init();
		std::string ReadShader(const std::string& shaderFileName);
		GLuint CreateShader(GLuint shaderType, 
							const std::string& shaderSource,
							const std::string& shaderName);
		
		static std::map<std::string, GLuint> programs;

	};
}
#endif
