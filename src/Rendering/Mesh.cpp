#include "Mesh.h"
#include <sstream>
#include <iostream>
#include <string>
using namespace std;
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
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
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
	// Vertex Texture Coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);
}

void Mesh::Draw(GLuint program, const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix, const glm::mat4& modelMatrix)
{
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUseProgram(program);

	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, false,
		&viewMatrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, false,
		&projectionMatrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, false,
		&modelMatrix[0][0]);

	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		int number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
			number = diffuseNr++; 
		else if (name == "texture_specular")
			number = specularNr++;
		else if (name == "texture_normal")
			number = normalNr++;
		else if (name == "texture_height")
			number = heightNr++;
		
		glUniform1i(glGetUniformLocation(program, (name + std::to_string(number)).c_str()), i);
		
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}


	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}