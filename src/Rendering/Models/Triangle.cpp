#include "Triangle.h"
#include "../Vertex.h"
#include <vector>
#include <iostream>
using namespace Rendering;
using namespace Models;

Triangle::Triangle()
{
    
}

Triangle::~Triangle()
{
    
}

void Triangle::Create()
{
    GLuint vao;
    GLuint vbo;
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    std::vector<Vertex> vertices;
    
    vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
    vertices.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec4));
    
     glBindVertexArray(0);
    
    this->vao = vao;
    this->vbos.push_back(vbo);
    
}

void Triangle::Update()
{
    
}

void Triangle::Draw()
{
    //std::cout << "Triangle" << std::endl;
    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
}
    
