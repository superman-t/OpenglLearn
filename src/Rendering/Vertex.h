//
//  Vertex.h
//  OpenglLearn
//
//  Created by AceTian on 2017/9/13.
//
//

#ifndef Vertex_h
#define Vertex_h

#include "../GLHealder.h"
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Rendering
{

	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
		glm::vec4 color;

		Vertex()
		{

		};

		Vertex(const glm::vec3& _pos, const glm::vec4& _color)
		{
			position = _pos;
			color = _color;
		}

		Vertex(const glm::vec3& _pos, const glm::vec3& _normal, const glm::vec2& _texCoords)
		{
			position = _pos;
			normal = _normal;
			texCoords = _texCoords;
		}
	};

	struct Texture
	{
		GLuint id;
		std::string type;
		aiString path;
	};

}
#endif /* Vertex_h */
