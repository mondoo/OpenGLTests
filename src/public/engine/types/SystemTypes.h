#pragma once

#include  <functional>
#include <string>

enum ResourceType
{
	Image
};

struct Resource
{
	std::string m_path;
	ResourceType m_type;
	struct Resource* next;
};
