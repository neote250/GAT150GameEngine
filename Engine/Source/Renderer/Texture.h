#pragma once

#include "../Resource/Resource.h"
#include "../Math/Vector2.h"
#include <string>

struct SDL_Texture;

class Texture : public Resource
{
public:
	Texture() = default;
	~Texture();

	bool Load(const std::string& filename, class Renderer& renderer);
	bool Create(std::string name, ...) override;
	Vector2 GetSize();

	friend class Renderer;

private:
	struct SDL_Texture* _texture{ nullptr };
};