#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include "../GLHealder.h"
#include <vector>

namespace Rendering
{
	class IGameObject
	{
	public:
        virtual ~IGameObject() = 0;
        
        virtual void Draw() = 0;
        virtual void Draw(const glm::mat4& projectionMatrix,
                          const glm::mat4& viewMatrix,
						  const glm::mat4& modelMatrix)=0;
        virtual void Update() = 0;
        virtual void SetProgram(GLuint shader) = 0;
        virtual void Destroy() = 0;
        
        virtual GLuint GetVao() const = 0;
        virtual const std::vector<GLuint>& GetVbos() const = 0;
	};
    inline IGameObject::~IGameObject()
    {
         
    }
}
#endif
