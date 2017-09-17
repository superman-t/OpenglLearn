#ifndef MODEL_H
#define MODEL_H

#include "../IGameObject.h"

namespace Rendering {
    namespace Models
    {
        class Model : public IGameObject
        {
        public:
            Model();
            ~Model();
            
            virtual void Draw() override;
            virtual void Draw(const glm::mat4& projectionMatrix,
                              const glm::mat4& viewMatrix) override;
            virtual void Update() override;
            virtual void SetProgram(GLuint program) override;
            virtual void Destroy() override;
            
            GLuint GetVao() const override;
            const std::vector<GLuint>& GetVbos() const override;
            
        protected:
            GLuint vao;
            GLuint program;
            std::vector<GLuint> vbos;
        };
    }
}

#endif
