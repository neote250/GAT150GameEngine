#pragma once

#include "Font.h"
#include "Renderer.h"
#include "Color.h"
#include "Resource/Resource.h"

class Text
{
public:

	Text() = default;
	Text(res_t<Font> font) : _font{ font } {}
	~Text();

	void SetFont(res_t<Font> font) { _font = font; }
	bool Create(Renderer& renderer, const std::string& text, const Color& color);
	void Draw(Renderer& renderer, int x, int y);

private:
	res_t<Font> _font;
	SDL_Texture* _texture{ nullptr };
};
