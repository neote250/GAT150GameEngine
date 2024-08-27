#include "CharacterComponent.h"
#include "Engine.h"

FACTORY_REGISTER(CharacterComponent)

void CharacterComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&CharacterComponent::OnCollisionEnter, this, std::placeholders::_1);
	owner->OnCollisionExit = std::bind(&CharacterComponent::OnCollisionEnter, this, std::placeholders::_1);

	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();

}

void CharacterComponent::Update(float dt)
{
	bool onGround = (groundCount > 0);
	Vector2 direction { 0,0 };
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

	float modifier = (onGround) ? 1 : 0.5f;
	physics->ApplyForce(direction * speed * 5 * modifier);


	//if(onGround)
	owner->GetComponent<PhysicsComponent>()->SetVelocity(Vector2{ 0,-500 });

	if (physics->velocity.x < -0.1f) animation->hflip = true;
	else if (physics->velocity.x > 0.1f) animation->hflip = false;

	if (Math::Abs(physics->velocity.x) > 0.1f) animation->SetAnimation("run");
	else animation->SetAnimation("idle");

}

void CharacterComponent::OnCollisionEnter(Actor* actor)
{
	/*EVENT_NOTIFY(PlayerDead);
	EVENT_NOTIFY_DATA(AddPoints, 100);*/

	if (actor->tag == "ground") groundCount++;
}

void CharacterComponent::OnCollisionExit(Actor* actor)
{
	if (actor->tag == "ground") groundCount--;

}


void CharacterComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void CharacterComponent::Write(json_t& value)
{
}
