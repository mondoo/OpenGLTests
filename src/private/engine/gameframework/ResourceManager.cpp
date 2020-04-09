#include "engine/gameframework/ResourceManager.h"

ResourceManager::ResourceManager()
	: m_head(nullptr)
	, m_tail(nullptr)
{}

ResourceManager::~ResourceManager()
{
	m_head = nullptr;
	delete m_head;
	m_tail = nullptr;
	delete m_tail;
}

Resource* ResourceManager::Create()
{
	Resource* temp = new Resource();
	temp->m_path = "Hello world!";
	temp->m_type = ResourceType::Image;

	Insert(temp);

	return temp;
}

void ResourceManager::Insert(Resource* resource)
{
	if (m_head == nullptr)
	{
		m_head = resource;
		m_tail = resource;
	}
	else
	{
		m_tail->next = resource;
		m_tail = m_tail->next;
	}
}

void ResourceManager::Remove(Resource* resource)
{
	Resource* previousResource = m_head;
	Resource* thisResource = m_head;
	while (thisResource != nullptr)
	{
		if (thisResource == resource)
		{
			previousResource->next = thisResource->next;

			thisResource = nullptr;
			delete thisResource;
			return;
		}

		previousResource = thisResource;
		thisResource = thisResource->next;
	}
}

Resource* ResourceManager::Find(std::function<bool(Resource*)> fn)
{
	Resource* thisResource = m_head;
	while (m_head != nullptr)
	{
		if (fn(thisResource))
		{
			return thisResource;
		}

		thisResource = thisResource->next;
	}
	return nullptr;
}