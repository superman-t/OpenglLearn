#ifndef Label_H
#define Label_H

#include <string>
#include <vector>
#include <iostream>
#include "../GLHealder.h"
#include "IGameObject.h"

namespace Rendering
{
	class Label : public IGameObject
	{
	public:
		Label();
		~Label();
		Label(const std::string& _text, unsigned int _size = 20, glm::vec2 _pos = glm::vec2(100, 100));

		virtual void Draw() override;
		virtual void Draw(const glm::mat4& projectionMatrix,
			const glm::mat4& viewMatrix,
			const glm::mat4& modelMatrix) override
		{};
		virtual void Update() override;
		virtual void SetProgram(GLuint program) override;
		virtual void Destroy() override;

		GLuint GetVao() const override;
		const std::vector<GLuint>& GetVbos() const override;

		void SetSize(unsigned int _size) {
			size = _size;
		}

		void SetPosition(glm::vec2 _pos)
		{
			pos = _pos;
		}

		void SetString(const std::string& _text)
		{
			text = _text;
		}
		
	protected:
		GLuint vao;
		std::vector<GLuint> vbos;
		GLuint program;

	private:
		void Create();
		GLuint LoadDDS(const char * imagepath);
	private:
		std::string text;
		unsigned int size;
		glm::vec2 pos;
		GLuint texturebo;
		GLuint vbo;
		unsigned int Text2DTextureID;
		unsigned int Text2DUniformID;
		unsigned int verticesize;
	};

	
}

#endif