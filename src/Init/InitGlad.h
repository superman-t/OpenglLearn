#if defined(TARGET_PLATFORM_WINDOWS) || defined(WIN32)
#include <glad/glad.h>
#endif 

namespace Init {
	class InitGlad {
	public:
		static void Init();
	};

	void InitGlad::Init()
	{

	}
}