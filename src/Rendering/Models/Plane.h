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
            virtual void Draw() override final;
        };
    }
}

#endif
