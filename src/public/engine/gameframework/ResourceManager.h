#pragma once

#include <functional>
#include <vector>

#include "engine/types/SystemTypes.h"

class ResourceManager
{
public:
	ResourceManager();

	~ResourceManager();

	Resource* Create(char* name, void* asset, ResourceType type);
	void Insert(Resource* resource);
	void Remove(Resource* resource);

	template<typename T = Texture>
	T* Find(char* name);

	Resource* Find(std::function<bool(Resource*)> fn);

	template<typename T = Texture>
	void FilterByType(std::vector<T*>& collection, ResourceType type);

private:
	Resource* m_head;
	Resource* m_tail;
};

template<typename T>
inline T* ResourceManager::Find(char* name)
{
	Resource* resource = Find([&name](Resource* compare) {
		return strcmp(compare->m_name, name) == 0;
	});

	if (resource != nullptr)
	{
		return (T*)resource->m_resource;
	}

	return nullptr;
}

template<typename T>
void ResourceManager::FilterByType(std::vector<T*>& collection, ResourceType type)
{
	Resource* thisResource = m_head;
	while (thisResource != nullptr)
	{
		if (thisResource->m_type == type)
		{
			collection.push_back((T*)thisResource->m_resource);
		}

		thisResource = thisResource->next;
	}
}