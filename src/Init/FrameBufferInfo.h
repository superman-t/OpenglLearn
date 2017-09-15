#include "../GLHealder.h"
struct FrameBufferInfo
{
	unsigned int flags;
	bool mutilSample;

	FrameBufferInfo()
	{
		flags = GL_DEPTH | GL_DOUBLE | GL_RGBA;
		mutilSample = false;
	}

	FrameBufferInfo(bool color, bool stencil, bool depth, bool mass)
		:mutilSample(mass)
	{
		flags = GL_DOUBLE;// double buffer
		if (color)
			flags |= GL_RGBA | GL_ALPHA;
		if (stencil)
			flags |= GL_STENCIL;
		if (depth)
			flags |= GL_DEPTH;
		if (mass)
			flags |= GL_MULTISAMPLE;
	}

	FrameBufferInfo(const FrameBufferInfo& fb)
	{
		flags = fb.flags;
		mutilSample = fb.mutilSample;
	}


	void operator=(const FrameBufferInfo& fb)
	{
		flags = fb.flags;
		mutilSample = fb.mutilSample;
	}

};