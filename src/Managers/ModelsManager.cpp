//
//  ModelsManager.cp
//  OpenglLearn
//
//  Created by AceTian on 2017/9/16.
//
//

#include "ModelsManager.h"
#include "../Rendering/Models/Plane.h"
using namespace Rendering;
using namespace Managers;
using namespace Models;

ModelsManager::ModelsManager()
{
	Plane* plane = new Plane(50, 50);
	plane->SetProgram(ShaderManager::getInstance()->GetShader("plane"));
	gameModelList["plane"] = plane;
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

void ModelsManager::Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix)
{
    for(auto model: gameModelList)
    {
        model.second->Draw(projectionMatrix, viewMatrix, modelMatrix);
    }
}

void ModelsManager::AddModel(const std::string &gameObjectName, Rendering::IGameObject *gameObject)
{
    gameModelList[gameObjectName] = gameObject;
}

void ModelsManager::AddModelNDC(const std::string &gameObjectName, IGameObject* gameObject)
{
	gameModelListNDC[gameObjectName] = gameObject;
}
