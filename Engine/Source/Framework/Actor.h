#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Components/Component.h"
#include <string>
#include <memory>
#include <vector>

class Renderer;
class Scene;

class Actor : public Object
{
public:
	Actor() {}
	Actor(const Transform& transform):_transform{ transform }{}

	void Initialize() override;
	virtual void Update(float dt);
	virtual void Draw(Renderer& renderer);

	void AddComponent(std::unique_ptr<Component> component);

	void SetDamping(float damping) { _damping = damping; }
	void SetLifespan(float lifespan) { _lifespan = lifespan; }
	const Transform& GetTranform() { return _transform; }
	void SetTag(const std::string tag) { _tag = tag; }
	const std::string& GetTag() { return _tag; }
	float GetRadius() { return (0); }

	virtual void OnCollision(Actor* actor) {}

	friend class Scene;

protected:
	std::string _tag;
	bool _destroyed = false;
	float _lifespan = 0;


	Transform _transform;
	Vector2 _velocity{0,0};
	float _damping{0};

	Scene* _scene{ nullptr };

	std::vector<std::unique_ptr<Component>> _components;
};