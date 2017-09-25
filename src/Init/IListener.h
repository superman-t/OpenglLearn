#ifndef ILISTENER_H
#define ILISTENER_H

class IListener
{
public:
	
	virtual ~IListener() = 0;

	virtual void NotifyBeginFrame(GLfloat deltaTime) = 0;
	virtual void NotifyRenderFrame(GLfloat deltaTime) = 0;
	virtual void NotifyEndFrame(GLfloat deltaTime) = 0;
	virtual void NotifyReshape(int width, int height, int previousWidth, int previousHeight) = 0;
    virtual void NotifyKeyInput(int key, int scancode, int action, int mode) = 0;
    virtual void NotifyMouseMove(double xpos, double ypos) = 0;
    virtual void NotifyScrollMove(double xoffset, double yoffset) = 0;
};

inline IListener::~IListener()
{

}


#endif
