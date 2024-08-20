#pragma once
#include "Resource.h"
#include "../Core/Singleton.h"
#include "Core/EString.h"
#include <map>
#include <iostream>

class ResourceManager : public Singleton<ResourceManager>
{
public:
	void Clear() { _resources.clear(); }

	template<typename T, typename ... TArgs>
	res_t<T> Get(const std::string& name, TArgs ... args);

	friend class Singleton;

protected:
	ResourceManager() = default;

private:
	std::map<std::string, res_t<Resource>> _resources;
};

template<typename T, typename ... TArgs>
inline res_t<T> ResourceManager::Get(const std::string& name, TArgs ... args)
{
	std::string lowerName = ToLower(name);



	// find resource in resource manager
	if (_resources.find(lowerName) != _resources.end())
	{
		// return resource
		return std::dynamic_pointer_cast<T>(_resources[lowerName]);
	}

	// resource not found, create resource
	res_t<T> resource = std::make_shared<T>();
	if (!resource->Create(lowerName, args...))
	{
		// resource not created
		std::cerr << "Could not create resource: " << lowerName << std::endl;
		return res_t<T>();
	}

	// add resource to resource manager
	_resources[lowerName] = resource;

	return resource;
}