//
//  Cube.cpp
//  OpenglLearn
//
//  Created by AceTian on 2017/9/16.
//
//

#include "Cube.h"

using namespace Rendering;
using namespace Models;

Cube::Cube()
{
    
}

Cube::~Cube()
{
    
}

void Cube::Create()
{
    GLuint vao;
    GLuint vbo;
    
    time(&timer);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    std::vector<Vertex> vertices;
    //vertices for the front face of the cube
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, 1.0),
                                    glm::vec4( 0.0,  0.0, 1.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(1.0, -1.0, 1.0),
                                    glm::vec4(1.0,  0.0, 1.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(1.0, 1.0, 1.0),
                                    glm::vec4(1.0, 1.0, 1.0, 1.0)));
    
    vertices.push_back(Vertex(glm::vec3(-1.0, 1.0, 1.0),
                                    glm::vec4( 0.0, 1.0, 1.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(1.0, 1.0, 1.0),
                                    glm::vec4(1.0, 1.0, 1.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, 1.0),
                                    glm::vec4( 0.0,  0.0, 1.0, 1.0)));
    
    //vertices for the right face of the cube
    vertices.push_back(Vertex(glm::vec3(1.0, 1.0, 1.0),
                                    glm::vec4(1.0, 1.0, 1.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(1.0, 1.0, -1.0),
                                    glm::vec4(1.0, 1.0,  0.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(1.0, -1.0, -1.0),
                                    glm::vec4(1.0,  0.0 , 0.0, 1.0)));
    
    vertices.push_back(Vertex(glm::vec3(1.0, 1.0, 1.0),
                                    glm::vec4(1.0, 1.0, 1.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(1.0, -1.0, -1.0),
                                    glm::vec4(1.0,  0.0, 0.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(1.0, -1.0, 1.0),
                                    glm::vec4(1.0,  0.0, 1.0, 1.0)));
    
    //vertices for the back face of the cube
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, -1.0),
                                    glm::vec4( 0.0,  0.0,  0.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(1.0, -1.0, -1.0),
                                    glm::vec4(1.0,  0.0,  0.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(1.0, 1.0, -1.0),
                                    glm::vec4(1.0, 1.0,  0.0, 1.0)));
    
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, -1.0),
                                    glm::vec4( 0.0,  0.0,  0.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(1.0, 1.0, -1.0),
                                    glm::vec4(1.0, 1.0,  0.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(-1.0, 1.0, -1.0),
                                    glm::vec4( 0.0, 1.0,  0.0, 1.0)));
    
    //vertices for the left face of the cube
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, -1.0),
                                    glm::vec4( 0.0, 0.0, 0.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, 1.0),
                                    glm::vec4( 0.0,  0.0, 1.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(-1.0, 1.0, 1.0),
                                    glm::vec4( 0.0, 1.0, 1.0, 1.0)));
    
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, -1.0),
                                    glm::vec4( 0.0,  0.0,  0.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(-1.0, 1.0, 1.0),
                                    glm::vec4( 0.0, 1.0, 1.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(-1.0, 1.0, -1.0),
                                    glm::vec4(0.0, 1.0, 0.0, 1.0)));
    
    //vertices for the upper face of the cube
    vertices.push_back(Vertex(glm::vec3(1.0, 1.0, 1.0),
                                    glm::vec4(1.0, 1.0, 1.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(-1.0, 1.0, 1.0),
                                    glm::vec4( 0.0, 1.0, 1.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(1.0, 1.0, -1.0),
                                    glm::vec4(1.0, 1.0,  0.0, 1.0)));
    
    vertices.push_back(Vertex(glm::vec3(-1.0, 1.0, 1.0),
                                    glm::vec4( 0.0, 1.0, 1.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(1.0, 1.0, -1.0),
                                    glm::vec4(1.0, 1.0,  0.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(-1.0, 1.0, -1.0),
                                    glm::vec4( 0.0, 1.0, 0.0, 1.0)));
    
    //vertices for the bottom face of the cube
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, -1.0),
                                    glm::vec4( 0.0,  0.0, 0.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(1.0, -1.0, -1.0),
                                    glm::vec4(1.0,  0.0,  0.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, 1.0),
                                    glm::vec4( 0.0,  0.0, 1.0, 1.0)));
    
    vertices.push_back(Vertex(glm::vec3(1.0, -1.0, -1.0),
                                    glm::vec4(1.0,  0.0, 0.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, 1.0),
                                    glm::vec4( 0.0,  0.0, 1.0, 1.0)));
    vertices.push_back(Vertex(glm::vec3(1.0, -1.0, 1.0),
                                    glm::vec4(1.0,  0.0, 1.0, 1.0)));
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (void*)offsetof(Vertex, color));

    glBindVertexArray(0);
    this->vao = vao;
    this->vbos.push_back(vbo);
    
    rotationSpeed = glm::vec3(90.0, 90.0, 90.0);
    rotation = glm::vec3(0.0, 0.0, 0.0);
}

void Cube::Draw(const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix)
{
    //glDisable(GL_CULL_FACE);
    rotation = 0.01f * rotationSpeed + rotation;
    
    glm::vec3 rotationSin = glm::vec3(rotation.x * glm::pi<float>()/180,
                                      rotation.y * glm::pi<float>()/180,
                                      rotation.z * glm::pi<float>()/180);
    
    glUseProgram(program);
    glUniform3f(glGetUniformLocation(program, "rotation"),
                rotationSin.x, rotationSin.y, rotationSin.z);
    
    glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, false,
                       &viewMatrix[0][0]);
    
    glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, false,
                       &projectionMatrix[0][0]);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    
    
}

void Cube::Update()
{
    
}
