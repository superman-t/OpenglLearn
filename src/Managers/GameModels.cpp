//
//  GameModels.cpp
//  OpenglLearn
//
//  Created by AceTian on 2017/9/13.
//
//

#include "GameModels.h"
using namespace Models;
using namespace Rendering;

GameModels::GameModels(){}

GameModels::~GameModels()
{
    std::map<std::string, Model>::iterator it;
    for(it = GameModelList.begin(); it != GameModelList.end(); ++it)
    {
        unsigned int p = it->second.vao;
        glDeleteVertexArrays(1, &p);
        glDeleteBuffers(it->second.vbos.size(), &it->second.vbos[0]);
        it->second.vbos.clear();
    }
    GameModelList.clear();
}

void GameModels::CreateTriangleModel(const std::string &gameModelName)
{
    unsigned int vao;
    unsigned int vbo;
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    std::vector<Vertex> vertices;
    
    vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    vertices.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
                       
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));
    
    Model m;
    m.vao = vao;
    m.vbos.push_back(vbo);
    GameModelList[gameModelName] = m;
}


void GameModels::DeleteModel(const std::string &gameModelName)
{
    Model m = GameModelList[gameModelName];
    unsigned int p = m.vao;
    glDeleteVertexArrays(1, &p);
    glDeleteBuffers(m.vbos.size(), &m.vbos[0]);
    m.vbos.clear();
    GameModelList.erase(gameModelName);
}

unsigned int GameModels::GetModel(const std::string &gameModelName)
{
    return GameModelList[gameModelName].vao;
}

