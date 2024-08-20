#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Components/Component.h"
#include "Core/Json.h"
#include <string>
#include <memory>
#include <vector>
#include <functional>

class Renderer;
class Scene;

class Actor : public Object
{
public:
	Actor() {}
	Actor(const Transform& transform):transform{ transform }{}

	CLASS_DECLARATION(Actor)

	void Initialize() override;
	virtual void Update(float dt);
	virtual void Draw(Renderer& renderer);
	
	std::function<void(Actor*)> OnCollisionEnter;

	void AddComponent(std::unique_ptr<Component> component);

	template<typename T>
	T* GetComponent();

	template<typename T>
	std::vector<T*> GetComponents();

	friend class Scene;

public:
	std::string tag;
	float lifespan = 0;
	bool destroyed = false;
	Transform transform;
	Scene* scene{ nullptr };

protected:

	std::vector<std::unique_ptr<Component>> components;
};

template<typename T>
inline T* Actor::GetComponent()
{
	for (auto& component : components) {
		T* result = dynamic_cast<T*>(component.get());
		if (result) return result;
	}

	return nullptr;
}

template<typename T>
inline std::vector<T*> Actor::GetComponents()
{
	std::vector<T*> results;
	for (auto& component : components) {
		T* result = dynamic_cast<T*>(component.get());
		if (result) results.push_back(result);
	}

	return results;
}
