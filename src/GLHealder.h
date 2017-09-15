#ifndef GLHEALDER_H
#define GLHEALDER_H

#if defined(TARGET_PLATFORM_WINDOWS) || defined(WIN32)
#include <glad/glad.h>
#endif 

#if defined(TARGET_PLATFORM_MAC) || defined(TARGET_PLATFORM_IOS)
#include <OpenGL/GL3.h>
#endif 

#include <GLFW/glfw3.h>

#endif // !GLHEALDER_H