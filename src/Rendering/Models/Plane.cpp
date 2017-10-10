#include "Plane.h"
#include "../Vertex.h"
#include <iostream>
#include <vector>

using namespace Rendering;
using namespace Models;

Plane::Plane(int _width, int _height) :width(_width), height(_height)
{

}


Plane::~Plane()
{
    
}

void Plane::Create()
{
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    std::vector<Vertex> vertices;
    
    for (int x = -width; x <= width; ++x)
    {
        vertices.push_back(Vertex(glm::vec3(x, 0.0f, height), glm::vec4(0.2f, 0.3f, 0.4f, 1.0f)));
        vertices.push_back(Vertex(glm::vec3(x, 0.0f, -height), glm::vec4(0.2f, 0.3f, 0.4f, 1.0f)));
    }
    
    for (int z = -height; z <= height; ++z)
    {
        vertices.push_back(Vertex(glm::vec3(width, 0.0f, z), glm::vec4(0.2f, 0.3f, 0.4f, 1.0f)));
        vertices.push_back(Vertex(glm::vec3(-width, 0.0f, z), glm::vec4(0.2f, 0.3f, 0.4f, 1.0f)));
    }
    
    
    verticesize = vertices.size();
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesize*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    
    glBindVertexArray(0);
    
    this->vao = vao;
    this->vbos.push_back(vbo);    
}

void Plane::SetSize(int _width, int _height)
{
	width = _width;
	height = _height;
}


void Plane::Update()
{
    
}

void Plane::Draw(const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix)
{

    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, false,
                       &viewMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, false,
                       &projectionMatrix[0][0]);
    // draw plane
	glUniform1i(glGetUniformLocation(program, "line"), 0);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, verticesize);

    // draw lines
	glUniform1i(glGetUniformLocation(program, "line"), 1);
	glDrawArrays(GL_LINES, 0, verticesize);
}
