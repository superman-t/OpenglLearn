#ifndef GLHEALDER_H
#define GLHEALDER_H

#if defined(TARGET_PLATFORM_WINDOWS) || defined(WIN32)
#include <glad/glad.h>
#endif 

#if defined(TARGET_PLATFORM_MAC) || defined(TARGET_PLATFORM_IOS)
#include <OpenGL/GL3.h>
#endif 

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef TARGET_COMPILE_XCODE
#define ROOTPATH "../../"
#else
#define ROOTPATH "../"
#endif

#endif // !GLHEALDER_H
