//
//  Quad.h
//  OpenglLearn
//
//  Created by AceTian on 2017/9/16.
//
//

#ifndef Quad_h
#define Quad_h

#include "Model.h"

namespace Rendering
{
    namespace Models
    {
        class Quad : public Model
        {
        public:
            Quad();
            ~Quad();
            
            void Create();
            
            virtual void Update() override final;//can't override by child class
            virtual void Draw() override final;
        };
    }
}
#endif /* Quad_h */
