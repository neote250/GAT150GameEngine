#include "Scene.h"
#include "Actor.h"
#include "Core/Factory.h"
#include "Core/EAssert.h"
#include "Components/CollisionComponent.h"
#include <algorithm>

Scene::Scene(const Scene& other)
{
	ASSERT(false);
}

void Scene::Initialize()
{
	for (auto& actor : _actors) { actor->Initialize(); }
}

void Scene::Update(float dt)
{
	//update
	for (auto& actor : _actors) { if (actor->active) actor->Update(dt);}

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

void Scene::AddActor(std::unique_ptr<Actor> actor, bool initialize)
{
	actor->scene = this;
	if (initialize) actor->Initialize();

	_actors.push_back(std::move(actor));
}

void Scene::RemoveAll(bool isTrue)
{
	_actors.clear();
	//std::erase_if(_actors, [force](auto& actor) {return(force || actor->destroyed;)!actor->persistent); });
}


void Scene::Read(const json_t& value)
{
	if (HAS_DATA(value, _actors) && GET_DATA(value, _actors).IsArray())
	{
		for (auto& actorValue : GET_DATA(value, _actors).GetArray())
		{
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			bool prototype = false;
			READ_DATA(actorValue, prototype);

			if (prototype) {
				std::string name = actor->name;
				Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
			}
			else {
				AddActor(std::move(actor));
			}
		}
	}
}
void Scene::Write(json_t& value)
{
}