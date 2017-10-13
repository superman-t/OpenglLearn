#ifndef Mesh_h
#define Mesh_h

#include "../GLHealder.h"
#include <glm/glm.hpp>
#include "Vertex.h"
#include <vector>

namespace Rendering
{
	class Mesh 
	{
	public:
		/*  Mesh Data  */
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
		// Render the mesh
		void Draw(GLuint program, const glm::mat4& projectionMatrix,
			const glm::mat4& viewMatrix, const glm::mat4& modelMatrix);
	private:
		/*  Render data  */
		GLuint VAO, VBO, EBO;
		void SetupMesh();
	};
}

#endif