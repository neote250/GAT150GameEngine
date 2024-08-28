#include "Actor.h"
#include "Components/RenderComponent.h"
#include "Core/Factory.h"
//#include "Object.h"
//#include "Core/Json.h"
#include <iostream>

FACTORY_REGISTER(Actor)

Actor::Actor(const Actor& other)
{
	tag = other.tag;
	lifespan = other.lifespan;
	destroyed = other.destroyed;
	persistent = other.persistent;
	transform = other.transform;
	scene = other.scene;

	for (auto& component : other.components)
	{
		auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
		AddComponent(std::move(clone));
	}
}

void Actor::Initialize()
{
	for (auto& component : components)
	{
		component->Initialize();
	}
}

void Actor::Update(float dt)
{
	//check for lifespan
	if (lifespan != 0) {
		lifespan -= dt;
		if (lifespan <= 0) {
			destroyed = true;
		}
	}

	for (auto& component : components)
	{
		component->Update(dt);
	}

	//transform.position += (_velocity * dt);
	//_velocity *= 1.0f / (1.0f + _damping * dt);
}

void Actor::Draw(Renderer& renderer)
{
	if (destroyed) return;

	for (auto& component : components)
	{
		RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component.get());
		if (renderComponent) 
		{
			renderComponent->Draw(renderer);
		}
	}

}

void Actor::AddComponent(std::unique_ptr<Component> component)
{
	component->owner = this;
	components.push_back(std::move(component));
}

void Actor::Read(const json_t& value)
{
	Object::Read(value);

	READ_DATA(value, tag);
	READ_DATA(value, lifespan);
	//read transform
	if (HAS_DATA(value, transform)) transform.Read(GET_DATA(value, transform));
	//read components
	if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
	{
		for (auto& componentValue : GET_DATA(value, components).GetArray())
		{
			std::string type;
			READ_DATA(componentValue, type);


			auto component = Factory::Instance().Create<Component>(type);
			if (!component)
			{
				std::cerr << "Could not create component: " << type << std::endl;
				continue;
			}

			component->Read(componentValue);

			AddComponent(std::move(component));
		}
	}
}

void Actor::Write(json_t& value)
{
}