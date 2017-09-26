#ifndef Plane_h
#define Plane_h

#include "Model.h"

namespace Rendering {
    namespace Models
    {
        class Plane : public Model
        {
        public:
            Plane();
            ~Plane();
            
            void Create();
            
            virtual void Update() override final;
            virtual void Draw(const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix) override final;
            
        private:
            int verticesize;
        };
    }
}

#endif
