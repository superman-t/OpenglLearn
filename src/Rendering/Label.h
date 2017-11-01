#ifndef Label_H
#define Label_H

#include <string>
#include <vector>
#include <iostream>
#include "../GLHealder.h"

namespace Rendering
{
	class Label
	{
	public:
		Label();
		Label(std::string& _text);
		Label(std::string& _text, unsigned int _size);
		Label(std::string& _text, unsigned int _size, glm::vec2 _pos);
		void SetSize(unsigned int _size) {
			size = _size;
		}

		void SetPosition(glm::vec2 _pos)
		{
			pos = _pos;
		}

		void SetString(std::string& _text)
		{
			text = _text;
		}

		void Update();
		void Draw();

		~Label();

	private:
		void Create();
	private:
		std::string text;
		unsigned int size;
		glm::vec2 pos;
		GLuint texturebo;
		GLuint vbo;
	};

	
}

#endif