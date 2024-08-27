#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <memory>

struct Transform;

class Renderer {
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();

	bool CreateWindow(std::string title, int width, int height);
	void BeginFrame();
	void EndFrame();

	void DrawRect(int x, int y, int w, int h);
	void DrawRect(float x, float y, float w, float h);
	

	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a=0);//unsigned int 8 bit // ctrl click to get the info
	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawPoint(int x, int y);
	void DrawPoint(float x, float y);
	
	void DrawTexture(std::weak_ptr<class Texture> texture, float x, float y, float angle = 0.0f);
	void DrawTexture(std::weak_ptr<class Texture> texture, const Transform& transform, bool hflip = false);
	void DrawTexture(std::weak_ptr<class Texture> texture, const Transform& transform, const struct Rect& source, bool hflip = false);

	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }

	friend class Text;
	friend class Texture;


protected:
	SDL_Window* _window{ nullptr };
	SDL_Renderer* _renderer{ nullptr };

	int _width{ 0 };
	int _height{ 0 };
};