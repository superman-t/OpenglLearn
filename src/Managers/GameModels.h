//
//  GameModels.h
//  OpenglLearn
//
//  Created by AceTian on 2017/9/13.
//
//

#ifndef GameModels_h
#define GameModels_h

#include "../GLHealder.h"

#include "../Vertex.h"
#include <vector>
#include <map>
#include <string>

namespace Models {
    struct Model{
        unsigned int vao;
        std::vector<unsigned int> vbos;
        
        Model(){}
    };
    
    class GameModels{
    public:
        GameModels();
        ~GameModels();
        
        void CreateTriangleModel(const std::string& gameModelName);
        void DeleteModel(const std::string& gameModelName);
        unsigned int GetModel(const std::string& gameModelName);
        
    private:
        std::map<std::string, Model> GameModelList;
    };
}

#endif /* GameModels_h */
