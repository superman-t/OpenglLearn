#include <string>
struct WindowInfo {
	std::string name;
	unsigned int width, height;
	unsigned int posx, posy;
	bool isReshapble;

	WindowInfo()
	{
		name = "OpenglLearnTutorial";
		width = 800;
		height = 480;
		posx = posy = 300;
		isReshapble = true;
	}

	WindowInfo(const WindowInfo& w)
	{
		name = w.name;
		width = w.width;
		height = w.height;
		posx = w.posx;
		posy = w.posy;
		isReshapble = w.isReshapble;
	}

	WindowInfo(std::string _name,
		unsigned int _width,
		unsigned int _height,
		unsigned int _posx,
		unsigned int _posy,
		bool _isReshapble)
		:name(_name),
		width(_width),
		height(_height),
		posx(_posx),
		posy(_posy),
		isReshapble(_isReshapble)
	{

	}

	void operator=(const WindowInfo& w)
	{
		name = w.name;
		width = w.width;
		height = w.height;
		posx = w.posx;
		posy = w.posy;
		isReshapble = w.isReshapble;
	}
};