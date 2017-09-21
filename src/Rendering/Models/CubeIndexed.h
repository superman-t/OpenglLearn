
#ifndef CubeIndexed_h
#define CubeIndexed_h

#include "Model.h"
#include <glm/glm.hpp>
#include "../Vertex.h"
#include <time.h>

namespace Rendering
{
    namespace Models
    {
        class CubeIndexed : public Model
        {
        public:
            CubeIndexed();
            ~CubeIndexed();
            
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

#endif
