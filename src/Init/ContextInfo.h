
struct ContextInfo{
	int major, minor;
	bool core;

	ContextInfo()
	{
		major = 3;
		minor = 3;
		core = true;
	}

	ContextInfo(const ContextInfo& con)
	{
		major = con.major;
		minor = con.minor;
		core = con.core;
	}

	ContextInfo(unsigned int _major, unsigned int _minor, bool _core)
		:major(_major), minor(_minor), core(_core)
	{
	}

	void operator=(const ContextInfo& con)
	{
		major = con.major;
		minor = con.minor;
		core = con.core;
	}


};