#pragma once

#include "Framework/Game.h"
#include "Event/EventManager.h"
#include <memory>

class SpaceGame : public Game, Observer
{
public:
	SpaceGame() = default;
	SpaceGame(Engine* engine) : Game{ engine } {}

	bool Initialize() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	//events
	void OnPlayerDead(const Event& event);
	void OnAddPoints(const Event& event);

private:
	std::unique_ptr<class Scene> _scene;
	float spawnTimer = 2;
};
