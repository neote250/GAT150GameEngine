#pragma once

//Core
#include "Core/EngineTime.h"
#include "Core/EAssert.h"
#include "Core/EFile.h"
#include "Core/EString.h"
#include "Core/Json.h"
#include "Core/Singleton.h"
#include "Core/Factory.h"
//Renderer
#include "Renderer/Renderer.h"
#include "Renderer/Particle.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"
//Resources
#include "Resource/Resource.h"
#include "Resource/ResourceManager.h"
//EventManager
#include "Event/EventManager.h"
//Components
#include "Components/TextureComponent.h"
#include "Components/EnginePhysicsComponent.h"
#include "Components/TextComponent.h"
#include "../../Game/Source/Components/PlayerComponent.h"
#include "Components/TextureAnimationComponent.h"
//Input
#include "Input/Input.h"
//Audio
#include "Audio/Audio.h"
//Math
#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"
#include "Math/Rect.h"
//Framework
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"
//Physics
#include "Physics/Physics.h"

#include <fmod.hpp>
#include <SDL.h>
#include <memory>

class Engine {
public:
	Engine() = default;
	~Engine(){}

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *_renderer; }
	Input& GetInput() { return *_input; }
	Audio& GetAudio() { return *_audio; }
	ParticleSystem& GetParticleSystem() { return *_particleSystem; }
	Time& GetTime() { return *_time; }
	bool IsQuit() { return quit; }

	Physics& GetPhysics() { return *_physics; }




private:
	bool quit{ false };

	std::unique_ptr <Physics> _physics;
	std::unique_ptr	<Time> _time;
	std::unique_ptr	<Renderer> _renderer;
	std::unique_ptr	<Input> _input;
	std::unique_ptr	<Audio> _audio;
	std::unique_ptr	<ParticleSystem> _particleSystem;
};