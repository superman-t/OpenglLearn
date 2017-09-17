//
//  Cube.h
//  OpenglLearn
//
//  Created by AceTian on 2017/9/16.
//
//

#ifndef Cube_h
#define Cube_h

#include "Model.h"
#include <glm/glm.hpp>
#include "../Vertex.h"
#include <time.h>

namespace Rendering {
    namespace Models
    {
        class Cube : public Model
        {
        public:
            Cube();
            ~Cube();
            
            void Create();
            
            virtual void Draw(const glm::mat4& projectionMatrix,
                              const glm::mat4& viewMatrix) override final;
            virtual void Update() override final;
            
        private:
            glm::vec3 rotation, rotationSpeed;
            time_t timer;
        };
    }
}

#endif /* Cube_h */
