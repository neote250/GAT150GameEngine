#include "Scene.h"
#include "Actor.h"
#include "Core/Factory.h"
#include "Components/CollisionComponent.h"
#include <algorithm>

void Scene::Initialize()
{
	for (auto& actor : _actors) { actor->Initialize(); }
}

void Scene::Update(float dt)
{
	//update
	for (auto& actor : _actors) { if (actor->active) actor->Update(dt);}

	//collision
	for (auto& actor1 : _actors) 
	{ 
		CollisionComponent* collision1 = actor1->GetComponent<CollisionComponent>();
		if (!collision1) continue;

		for (auto& actor2 : _actors)
		{
			//don't check with self
			if (actor1 == actor2)continue;

			CollisionComponent* collision2 = actor2->GetComponent<CollisionComponent>();
			if (!collision2) continue;

			if (collision1->CheckCollision(collision2))
			{
				//std::cout << "hit\n";
				if (actor1->OnCollisionEnter)actor1->OnCollisionEnter(actor2.get());
				if (actor2->OnCollisionEnter)actor2->OnCollisionEnter(actor1.get());
			}
		}
	}

	//destroy
	_actors.erase(
		std::remove_if(_actors.begin(), _actors.end(), [](auto& actor) {return actor->destroyed; })
		, _actors.end()
	);

}

void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : _actors) {
		if (actor->active) actor->Draw(renderer);
	}
}

void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	actor->scene = this;
	_actors.push_back(std::move(actor));
}

void Scene::RemoveAll()
{
	_actors.clear();
}

void Scene::Read(const json_t& value)
{
	if (HAS_DATA(value, _actors) && GET_DATA(value, _actors).IsArray())
	{
		for (auto& actorValue : GET_DATA(value, _actors).GetArray())
		{
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			AddActor(std::move(actor));
		}
	}
}
void Scene::Write(json_t& value)
{
}