#pragma once

#include "../Resource/Resource.h"
#include <sdl_ttf.h>
#include <string>


class Font : public Resource
{
public:
	Font() = default;
	~Font();

	bool Create(std::string name, ...) override;
	bool Load(const std::string& name, int fontSize);
	friend class Text;

protected:
	_TTF_Font* _ttfFont{ nullptr };
};
