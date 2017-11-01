#include "Label.h"


using namespace Rendering;
Label::Label()
{
}

Label::~Label()
{
}

Label::Label(std::string& _text)
{
	
}

Label::Label(std::string& _text, unsigned int _size) :text(_text), size(_size)
{

}

Label::Label(std::string& _text, unsigned int _size, glm::vec2 _pos):text(_text), size(_size), pos(_pos)
{

}

void Label::Draw()
{
	//glUseProgram();
}

void Label::Update()
{

}

void Label::Create()
{
	if (text == "") {
		std::cout << "Label text is empty" << std::endl;
		return;
	}
	int length = strlen(text.c_str());
	// Fill buffers
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;
	for (unsigned int i = 0; i<length; i++) {

		glm::vec2 tl = glm::vec2(pos.x + i*size, pos.y + size);//top left
		glm::vec2 tr = glm::vec2(pos.x + i*size + size, pos.y + size);
		glm::vec2 br = glm::vec2(pos.x + i*size + size, pos.y);
		glm::vec2 bl = glm::vec2(pos.x + i*size, pos.y);//bottom left

		vertices.push_back(tl);
		vertices.push_back(bl);
		vertices.push_back(tr);

		vertices.push_back(br);
		vertices.push_back(tr);
		vertices.push_back(bl);

		char character = text[i];
		float uv_x = (character % 16) / 16.0f;
		float uv_y = (character / 16) / 16.0f;

		glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
		glm::vec2 uv_up_right = glm::vec2(uv_x + 1.0f / 16.0f, uv_y);
		glm::vec2 uv_down_right = glm::vec2(uv_x + 1.0f / 16.0f, (uv_y + 1.0f / 16.0f));
		glm::vec2 uv_down_left = glm::vec2(uv_x, (uv_y + 1.0f / 16.0f));
		UVs.push_back(uv_up_left);
		UVs.push_back(uv_down_left);
		UVs.push_back(uv_up_right);

		UVs.push_back(uv_down_right);
		UVs.push_back(uv_up_right);
		UVs.push_back(uv_down_left);
	}
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &texturebo);
	glBindBuffer(GL_ARRAY_BUFFER, texturebo);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);


}