#pragma once

#include "Font.h"
#include "Renderer.h"
#include "Color.h"
#include "Resource/Resource.h"

class Texture;

class Text
{
public:

	Text() = default;
	Text(res_t<Font> font) : _font{ font } {}
	~Text() = default;

	bool Create(Renderer& renderer, const std::string& text, const Color& color);
	void Draw(Renderer& renderer, float x, float y, float angle = 0);

	void SetFont(res_t<Font> font) { _font = font; }
	res_t<Texture> GetTexture() { return _texture; }

private:
	res_t<Font> _font{ nullptr };
	res_t<Texture> _texture{ nullptr };
};
