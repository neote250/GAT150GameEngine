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

	switch (gameState)
	{
	case SpaceGame::eState::TITLE:
		if (_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
			_scene->GetActor<Actor>("text")->active = false;
			gameState = eState::GAME;
		}
		break;
	case SpaceGame::eState::STARTGAME:
		break;
	case SpaceGame::eState::GAME:
		batSpawnTimer -= dt;
		ghostSpawnTimer -= dt;


		if (batSpawnTimer <= 0)
		{
			auto bat =	Factory::Instance().Create<Actor>("bat");
			bat->transform.position = Vector2{ randomf(700)+100,randomf(300) };
			_scene->AddActor(std::move(bat), true);
			batSpawnTimer = 2;
		}
		if (ghostSpawnTimer <= 0)
		{
			auto ghost = Factory::Instance().Create<Actor>("ghost");
			ghost->transform.position = Vector2{ randomf(700)+100,randomf(300) };
			_scene->AddActor(std::move(ghost), true);
			ghostSpawnTimer = 4;
		}
		if (_scene->GetActor<Actor>("player")->transform.position.y > 650)
		{
			gameState = eState::GAMEOVER;

		}
		break;
	case SpaceGame::eState::PLAYERDEAD:
		break;
	case SpaceGame::eState::GAMEOVER:
		_scene->GetActor<Actor>("gameover")->active = true;
		break;
	default:
		break;
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
