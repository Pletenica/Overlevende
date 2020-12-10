#ifndef __Resource_H__
#define __Resource_H__

#include "Globals.h"
#include <string>


class Resource {
public:
	std::string name = "";
	std::vector<Resource*> children;
};

#endif // __Resource_H__