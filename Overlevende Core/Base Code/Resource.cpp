#include "Resource.h"

Resource::Resource()
{
	name = "";
	isDirectory = false;
}


Resource::Resource(const char* _name, bool _isDirectory)
{
	name = _name;
	isDirectory = _isDirectory;
}

Resource::~Resource()
{
	name = "";
	isDirectory = false;
	children.clear();
}
