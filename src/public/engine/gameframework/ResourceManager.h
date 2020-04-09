#pragma once

#include <functional>

#include "engine/types/SystemTypes.h"

class ResourceManager
{
public:
	ResourceManager();

	~ResourceManager();

	Resource* Create();
	void Insert(Resource* resource);
	void Remove(Resource* resource);

	Resource* Find(std::function<bool(Resource*)> fn);

private:
	Resource* m_head;
	Resource* m_tail;
};