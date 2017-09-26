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
    virtual void NotifyKeyInput(int key, int scancode, int action, int mode){};
    virtual void NotifyMouseMove(double xpos, double ypos){};
    virtual void NotifyScrollMove(double xoffset, double yoffset){};
};

inline IListener::~IListener()
{

}

//void NotifyKeyInput(int key, int scancode, int action, int mode)
//{
//    
//}
//
//void NotifyMouseMove(double xpos, double ypos)
//{
//    
//}
//
//void NotifyScrollMove(double xoffset, double yoffset)
//{
//    
//}


#endif
