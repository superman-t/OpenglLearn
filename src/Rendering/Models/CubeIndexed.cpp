
#include "CubeIndexed.h"
#include "glm/ext.hpp"
using namespace Rendering;
using namespace Models;

CubeIndexed::CubeIndexed()
{
    
}

CubeIndexed::~CubeIndexed()
{
    
}

void CubeIndexed::Create()
{
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    
    time(&timer);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    unsigned int indices[] = {
        0,  1,  2,  0,  2,  3,   //front
        4,  5,  6,  4,  6,  7,   //right
        8,  9,  10, 8,  10, 11,  //back
        12, 13, 14, 12, 14, 15,  //left
        16, 17, 18, 16, 18, 19,  //upper
        20, 21, 22, 20, 22, 23}; //bottom
    
    std::vector<Vertex> vertices;
    //front
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, 1.0),
                                    glm::vec4(0, 0, 1, 1)));
    vertices.push_back(Vertex(glm::vec3( 1.0, -1.0, 1.0),
                                    glm::vec4(1, 0, 1, 1)));
    vertices.push_back(Vertex(glm::vec3( 1.0, 1.0, 1.0),
                                    glm::vec4(1, 1, 1, 1)));
    vertices.push_back(Vertex(glm::vec3(-1.0, 1.0, 1.0),
                                    glm::vec4(0, 1, 1, 1)));
    
    //right
    vertices.push_back(Vertex(glm::vec3(1.0, 1.0, 1.0),
                                    glm::vec4(1, 1, 1, 1)));
    vertices.push_back(Vertex(glm::vec3(1.0, 1.0, -1.0),
                                    glm::vec4(1, 1, 0, 1)));
    vertices.push_back(Vertex(glm::vec3(1.0, -1.0, -1.0),
                                    glm::vec4(1, 0, 0, 1)));
    vertices.push_back(Vertex(glm::vec3(1.0, -1.0, 1.0),
                                    glm::vec4(1, 0, 1, 1)));
    
    //back
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, -1.0),
                                    glm::vec4(0, 0, 0, 1)));
    vertices.push_back(Vertex(glm::vec3( 1.0, -1.0, -1.0),
                                    glm::vec4(1, 0, 0, 1)));
    vertices.push_back(Vertex(glm::vec3( 1.0, 1.0, -1.0),
                                    glm::vec4(1, 1, 0, 1)));
    vertices.push_back(Vertex(glm::vec3(-1.0, 1.0, -1.0),
                                    glm::vec4(0, 1, 0, 1)));
    
    //left
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, -1.0),
                                    glm::vec4(0, 0, 0, 1)));
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, 1.0),
                                    glm::vec4(0, 0, 1, 1)));
    vertices.push_back(Vertex(glm::vec3(-1.0, 1.0, 1.0),
                                    glm::vec4(0, 1, 1, 1)));
    vertices.push_back(Vertex(glm::vec3(-1.0, 1.0, -1.0),
                                    glm::vec4(0, 1, 0, 1)));
    
    //upper
    vertices.push_back(Vertex(glm::vec3( 1.0, 1.0, 1.0),
                                    glm::vec4(1, 1, 1, 1)));
    vertices.push_back(Vertex(glm::vec3(-1.0, 1.0, 1.0),
                                    glm::vec4(0, 1, 1, 1)));
    vertices.push_back(Vertex(glm::vec3(-1.0, 1.0, -1.0),
                                    glm::vec4(0, 1, 0, 1)));
    vertices.push_back(Vertex(glm::vec3( 1.0, 1.0, -1.0),
                                    glm::vec4(1, 1, 0, 1)));
    
    //bottom
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, -1.0),
                                    glm::vec4(0, 0, 0, 1)));
    vertices.push_back(Vertex(glm::vec3( 1.0, -1.0, -1.0),
                                    glm::vec4(1, 0, 0, 1)));
    vertices.push_back(Vertex(glm::vec3( 1.0, -1.0, 1.0),
                                    glm::vec4(1, 0, 1, 1)));
    vertices.push_back(Vertex(glm::vec3(-1.0, -1.0, 1.0),
                                    glm::vec4(0, 0, 1, 1)));

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*24, &indices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    
    glBindVertexArray(0);
    this->vao = vao;
    this->vbos.push_back(vbo);
    this->vbos.push_back(ibo);
    
    rotationSpeed = glm::vec3(90.0, 90.0, 90.0);
    rotation = glm::vec3(0.0, 0.0, 0.0);
    
}

void CubeIndexed::Draw(const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix, const glm::mat4& modelMatrix)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUseProgram(program);
    
    glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, false,
                       &viewMatrix[0][0]);
    
    glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, false,
                       &projectionMatrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, false,
		&modelMatrix[0][0]);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
}

void CubeIndexed::Update()
{
    
}
