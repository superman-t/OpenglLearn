#ifndef Plane_h
#define Plane_h

#include "Model.h"

namespace Rendering {
    namespace Models
    {
        class Plane : public Model
        {
        public:
			Plane(int _width = 100, int _height = 100);
            ~Plane();
            
            void Create();
			void SetSize(int _width, int height);

            virtual void Update() override final;
            virtual void Draw(const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix,
							const glm::mat4& modelMatrix) override final;
            
        private:
            int verticesize;
			int width, height;

        };
    }
}

#endif
