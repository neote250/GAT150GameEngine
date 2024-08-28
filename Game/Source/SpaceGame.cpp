#include "SpaceGame.h"
#include "Engine.h"

#include <memory>
#include <functional>

bool SpaceGame::Initialize()
{
	//create, read and initialize scene
	_scene = std::make_unique<Scene>(_engine);

	std::string sceneNames[] = { "Scenes/tilemap.json", "Scenes/game.json" };
	for (auto sceneName : sceneNames)
	{
		//read json
		rapidjson::Document document;
		Json::Load(sceneName, document);
		_scene->Read(document);
	}

	_scene->Initialize();
	

	ADD_OBSERVER(PlayerDead, SpaceGame::OnPlayerDead)
	ADD_OBSERVER(AddPoints, SpaceGame::OnAddPoints)


    return true;
}

void SpaceGame::Shutdown()
{
	_scene->RemoveAll(true);
}

void SpaceGame::Update(float dt)
{
	spawnTimer -= dt;
	
	if(spawnTimer<=0)
	{
	auto bat = Factory::Instance().Create<Actor>("bat");
	bat->transform.position = Vector2{ randomf(800),randomf(300) };
	_scene->AddActor(std::move(bat), true);
	spawnTimer = 2;
	}

	_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer)
{
	_scene->Draw(renderer);
}

void SpaceGame::OnPlayerDead(const Event& event)
{
	std::cout << "game: player dead\n";
}

void SpaceGame::OnAddPoints(const Event& event)
{
	_score += std::get<int>(event.data);
	std::cout << _score << std::endl;
}
