//
//  ModelsManager.h
//  OpenglLearn
//
//  Created by AceTian on 2017/9/16.
//
//

#ifndef MODELSMANAGER_H
#define MODELSMANAGER_H

#include "ShaderManager.h"
#include "../Rendering/IGameObject.h"
#include "../Rendering/Models/Triangle.h"
#include "../Rendering/Models/Quad.h"
#include "../Rendering/Models/Cube.h"

#include <map>
#include <string>

using namespace Rendering;

namespace Managers
{
    class ModelsManager
    {
    public:
        ModelsManager();
        ~ModelsManager();
        
        void Draw();
        void Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
        void Update();
        
        void DeleteModel(const std::string& modelName);
        void DeleteModelNDC(const std::string& modelName);
        
        const IGameObject& GetModel(const std::string& modelName)const;
        
        const IGameObject& GetModelNDC(const std::string& modelName)const;
        
        void SetModel(const std::string& gameObjectName, IGameObject* gameObject);
        
    private:
        std::map<std::string, IGameObject*> gameModelList;
        std::map<std::string, IGameObject*> gameModelListNDC;
    };
}


#endif /* GameModels_h */
