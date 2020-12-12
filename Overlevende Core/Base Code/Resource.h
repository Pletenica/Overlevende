#ifndef __Resource_H__
#define __Resource_H__

#include "Globals.h"
#include <string>
#include <vector>

class Resource {
public:
	Resource();
	Resource(const char* _name, bool _isDirectory);
	~Resource();

	std::string name = "";
	bool isDirectory = false;
	std::vector<Resource> children;
	Resource* parent;
};

#endif // __Resource_H__