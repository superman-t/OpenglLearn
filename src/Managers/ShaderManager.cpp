#include "ShaderManager.h"
#include <vector>

using namespace Managers;

#ifdef WIN32
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

std::map<std::string, GLuint> ShaderManager::programs;
static ShaderManager* shaderManagerInstance = nullptr;
ShaderManager::ShaderManager()
{

}

ShaderManager* ShaderManager::getInstance()
{
	if (!shaderManagerInstance)
	{
		shaderManagerInstance = new ShaderManager();
		shaderManagerInstance->Init();
	}
	return shaderManagerInstance;
}

void ShaderManager::Init()
{

    std::string shaderPath(std::string(ROOTPATH) + "Shaders");

#ifdef WIN32
	 std::string filename, path;
	 for (fs::recursive_directory_iterator p(shaderPath); p != fs::recursive_directory_iterator{}; ++p)
	 {
	 	filename = p->path().string();
 
	 	int start = filename.find_last_of('\\');
	 	int end = filename.find_last_of(".");
	 	path = filename.substr(0, start);
	 	filename = filename.substr(start + 1, end - 1 - start);
	 	//std::cout << path + "/" + filename << std::endl;
	 	CreateProgram(filename, path + "/" + filename + ".vs", path + "/" + filename + ".fs");
	 }
	
#endif // WIN32

#ifdef TARGET_PLATFORM_MAC || TARGET_PLATFORM_IOS
	 std::string shaders[] = { "cube", "plane", "texture", "text" };
	std::vector<std::string> shaderNames(shaders, shaders + 4);
	for (int i = 0; i < shaderNames.size(); ++i)
	{
		std::string filename = shaderNames[i];
		CreateProgram(filename, shaderPath + "/" + filename + ".vs", shaderPath + "/" + filename + ".fs");
	}
#endif // TARGET_PLATFORM_MAC



	

}

ShaderManager::~ShaderManager()
{
	std::map<std::string, GLuint>::iterator it;
	for (it = programs.begin(); it != programs.end(); ++it)
	{
		GLuint p = it->second;
		glDeleteShader(p);
	}

	programs.clear();
}

std::string ShaderManager::ReadShader(const std::string& shaderFileName)
{
	std::string shaderCode;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		shaderFile.open(shaderFileName);
		std::stringstream shaderStream;

		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
    //std::cout << shaderCode<< std::endl;
	return shaderCode;
}

GLuint ShaderManager::CreateShader(GLuint shaderType, 
	const std::string& shaderSource,
	const std::string& shaderName)
{
	GLuint shader;
	shader = glCreateShader(shaderType);
	const char* code = shaderSource.c_str();
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

void ShaderManager::CreateProgram(const std::string& shaderName, 
	const std::string& vertexShaderFileName, 
	const std::string& fragmentShaderFileName)
{
	if (programs.find(shaderName) != programs.end())
		return;

	GLuint vs = CreateShader(GL_VERTEX_SHADER, ReadShader(vertexShaderFileName), shaderName);
	GLuint fs = CreateShader(GL_FRAGMENT_SHADER, ReadShader(fragmentShaderFileName), shaderName);
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
	
	programs[shaderName] = program;
}


const GLuint ShaderManager::GetShader(const std::string& shaderName)
{
	return programs[shaderName];
}
