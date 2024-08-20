#include "Renderer.h"
#include "Texture.h"
#include "Math/Vector2.h"
#include "Math/Transform.h"
#include <iostream>

bool Renderer::Initialize()
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	// initialize TTF SDL
	if (TTF_Init() < 0)
	{
		std::cerr << "Error initializing SDL TTF: " << SDL_GetError() << std::endl;
		return false;
	}

	// initialize Image SDL, supports BMP, JPG, and PNG
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
	{
		std::cerr << "Error initializing SDL Image: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Renderer::Shutdown()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	TTF_Quit();
	IMG_Quit();
}

bool Renderer::CreateWindow(std::string title, int width, int height)
{
	_width = width;
	_height = height;

	// create window
	// returns pointer to window if successful or nullptr if failed
	_window = SDL_CreateWindow(title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_SHOWN);
	if (_window == nullptr)
	{
		std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	// create renderer
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//if(_renderer == nullptr){}

	return true;
}

void Renderer::BeginFrame()
{
	SDL_RenderClear(_renderer);
}

void Renderer::EndFrame()
{
	SDL_RenderPresent(_renderer);
}

void Renderer::DrawRect(int x, int y, int w, int h)
{
	SDL_Rect rect{ x - w / 2,y - h / 2,w,h };
	SDL_RenderFillRect(_renderer, &rect);
}

void Renderer::DrawRect(float x, float y, float w, float h)
{
	SDL_FRect rect{ x - w / 2,y - h / 2,w,h };
	SDL_RenderFillRectF(_renderer, &rect);
}

void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

void Renderer::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
}

void Renderer::DrawLine(float x1, float y1, float x2, float y2)
{
	SDL_RenderDrawLineF(_renderer, x1, y1, x2, y2);
}

void Renderer::DrawPoint(int x, int y)
{
	SDL_RenderDrawPoint(_renderer, x, y);
}

void Renderer::DrawPoint(float x, float y)
{
	SDL_RenderDrawPointF(_renderer, x, y);
}

void Renderer::DrawTexture(std::weak_ptr<Texture> texture, float x, float y, float angle)
{
	Vector2 size = texture.lock()->GetSize();

	SDL_FRect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = size.x;
	destRect.h = size.y;

	// https://wiki.libsdl.org/SDL2/SDL_RenderCopyExF
	SDL_RenderCopyExF(_renderer, texture.lock()->_texture, NULL, &destRect, angle, NULL, SDL_FLIP_NONE);
}

void Renderer::DrawTexture(std::weak_ptr<Texture> texture, const Transform& transform, bool hflip)
{
	Vector2 size = texture.lock()->GetSize() * transform.scale;

	SDL_FRect destRect;
	destRect.x = transform.position.x;
	destRect.y = transform.position.y;
	destRect.w = size.x;
	destRect.h = size.y;

	// https://wiki.libsdl.org/SDL2/SDL_RenderCopyExF
	SDL_RenderCopyExF(_renderer, texture.lock()->_texture, NULL, &destRect, transform.rotation, NULL, (hflip) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
