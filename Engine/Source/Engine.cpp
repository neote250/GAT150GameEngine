#include "Engine.h"
#include <crtdbg.h>

bool Engine::Initialize()
{
    //enable memory leak check
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    _renderer = std::make_unique<Renderer>();
    _input = std::make_unique<Input>();
    _audio = std::make_unique<Audio>();
    _particleSystem = std::make_unique<ParticleSystem>();
    //_texture = std::make_unique<Texture>();
    _time = std::make_unique<Time>();
    
    _renderer->Initialize();
    _renderer->CreateWindow("Game Engine", 800, 600);

    _input->Initialize();

    _audio->Initialize();


    return true;
}

void Engine::Shutdown()
{
    _renderer->Shutdown();
    _input->Shutdown();
    _audio->Shutdown();


    //display memory leaks
    _CrtMemDumpAllObjectsSince(NULL);
}

void Engine::Update()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        quit = true;
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        quit = true;
    }

    _time->Tick();
    _input->Update();
    _particleSystem->Update(_time->GetDeltaTime());
    _audio->Update();
}
