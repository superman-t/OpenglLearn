#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Model.h"

namespace Rendering
{
    namespace Models
    {
        class Triangle : public Model
        {
        public:
            Triangle();
            ~Triangle();
            
            void Create();
            
            virtual void Update() override final;//can't override by child class
            virtual void Draw() override final;
        };
    }
}

#endif
