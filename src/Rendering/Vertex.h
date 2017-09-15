//
//  Vertex.h
//  OpenglLearn
//
//  Created by AceTian on 2017/9/13.
//
//

#ifndef Vertex_h
#define Vertex_h

#include "../../3rdparty/glm/glm.hpp"
namespace Rendering
{

	struct Vertex {
		glm::vec3 position;
		glm::vec3 color;

		Vertex(const glm::vec3& _pos, const glm::vec3& _color)
		{
			position = _pos;
			color = _color;
		}
	};
}
#endif /* Vertex_h */
