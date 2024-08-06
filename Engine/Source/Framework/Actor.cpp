#include "Actor.h"
#include "Components/RenderComponent.h"

void Actor::Initialize()
{
	for (auto& component : _components)
	{
		component->Initialize();
	}
}

void Actor::Update(float dt)
{
	//check for lifespan
	if (_lifespan != 0) {
		_lifespan -= dt;
		if (_lifespan <= 0) {
			_destroyed = true;
		}
	}

	for (auto& component : _components)
	{
		component->Update(dt);
	}

	_transform.position += (_velocity * dt);
	_velocity *= 1.0f / (1.0f + _damping * dt);
}

void Actor::Draw(Renderer& renderer)
{
	if (_destroyed) return;

	for (auto& component : _components)
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
	_components.push_back(std::move(component));
}

