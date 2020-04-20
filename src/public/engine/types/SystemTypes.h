#pragma once

#include <functional>
#include <string>
#include "engine/graphics/Texture.h"

enum class ResourceType : uint8_t
{
	Image,
	Shader,
	Font,
	Text,
	Light
};

struct Resource
{
	Resource(char* name, void* texture, ResourceType type)
		: m_name(name)
		, m_resource(texture)
		, m_type(type)
	{}

	~Resource()
	{
		m_resource = nullptr;
		delete m_resource;
		next = nullptr;
		delete next;
	}

	char* m_name;
	void* m_resource;
	ResourceType m_type = ResourceType::Image;

	struct Resource* next = nullptr;
};
