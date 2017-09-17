//
//  ModelsManager.cp
//  OpenglLearn
//
//  Created by AceTian on 2017/9/16.
//
//

#include "ModelsManager.h"

using namespace Rendering;
using namespace Managers;
using namespace Models;

ModelsManager::ModelsManager()
{
    //Triangle* triangle = new Triangle();
    //triangle->SetProgram(ShaderManager::GetShader("ColorShader"));
    //triangle->Create();
    //gameModelList["triangle"] = triangle;
    
    //Quad* quad = new Quad();
    //quad->SetProgram(ShaderManager::GetShader("ColorShader"));
    //quad->Create();
    //gameModelList["quad"] = quad;
    
    Cube* cube = new Cube();
    cube->SetProgram(ShaderManager::GetShader("ColorShader"));
    cube->Create();
    gameModelList["cube"] = cube;
    
}

ModelsManager::~ModelsManager()
{
    for(auto model:gameModelList)
    {
        delete model.second;
    }
    
    for(auto model:gameModelListNDC)
    {
        delete model.second;
    }
    
    gameModelList.clear();
    gameModelListNDC.clear();
}

void ModelsManager::DeleteModel(const std::string &modelName)
{
    IGameObject* model = gameModelList[modelName];
    model->Destroy();
    gameModelList.erase(modelName);
}

void ModelsManager::DeleteModelNDC(const std::string &modelName)
{
    IGameObject* model = gameModelListNDC[modelName];
    model->Destroy();
    gameModelListNDC.erase(modelName);
}

const IGameObject& ModelsManager::GetModel(const std::string &modelName) const
{
    return (*gameModelList.at(modelName));
}

const IGameObject& ModelsManager::GetModelNDC(const std::string &modelName) const
{
    return (*gameModelListNDC.at(modelName));
}

void ModelsManager::Update()
{
    for (auto model:gameModelList) {
        model.second->Update();
    }
    
    for(auto model:gameModelListNDC)
    {
        model.second->Update();
    }
}

void ModelsManager::Draw()
{
    for(auto model: gameModelListNDC)
    {
        model.second->Draw();
    }
}

void ModelsManager::Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
    for(auto model: gameModelList)
    {
        model.second->Draw(projectionMatrix, viewMatrix);
    }
}

void ModelsManager::SetModel(const std::string &gameObjectName, Rendering::IGameObject *gameObject)
{
    gameModelList[gameObjectName] = gameObject;
}
