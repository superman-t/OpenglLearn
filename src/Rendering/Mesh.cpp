#include "Mesh.h"

using namespace Rendering;

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	
	SetupMesh();
}

void Mesh::SetupMesh()
{
	// Create buffers/arrays
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	// Load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	// Vertex Normals
// 	glEnableVertexAttribArray(1);
// 	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
// 	// Vertex Texture Coords
// 	glEnableVertexAttribArray(2);
// 	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);
}

void Mesh::Draw(GLuint program, const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix)
{
	glm::mat4 modelMatrix(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0, 10.0f, 0.0));;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, false,
		&viewMatrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, false,
		&projectionMatrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, false,
		&modelMatrix[0][0]);

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}