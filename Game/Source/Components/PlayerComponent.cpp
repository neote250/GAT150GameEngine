#include "PlayerComponent.h"
#include "Engine.h"

FACTORY_REGISTER(PlayerComponent)

void PlayerComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1);
}

void PlayerComponent::Update(float dt)
{
	Vector2 direction{ 0,0 };
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
	owner->GetComponent<PhysicsComponent>()->ApplyForce({ direction*speed });
}

void PlayerComponent::OnCollisionEnter(Actor* actor)
{
	std::cout << "Player hit\n";
}

void PlayerComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void PlayerComponent::Write(json_t& value)
{
}
