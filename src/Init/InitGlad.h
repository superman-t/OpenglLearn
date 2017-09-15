#ifndef InitGlad_h
#define InitGlad_h

#include "../GLHealder.h"
#include <iostream>

namespace Init {
	class InitGlad {
	public:
		static void Init();
	};

	void InitGlad::Init()
	{
#if defined(TARGET_PLATFORM_WINDOWS) || defined(WIN32)
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return ;
		}
#endif
	}
}

#endif//InitGlad_h