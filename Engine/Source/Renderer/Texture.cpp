
//#include "../Core/EFile.h"
#include "Texture.h"
#include "../Core/EAssert.h"
#include "Renderer.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

Texture::~Texture()
{
    // if texture exists, destroy texture
    if (_texture) SDL_DestroyTexture(_texture);
}

bool Texture::Load(const std::string& filename, Renderer& renderer)
{
    // load image onto surface
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (!surface)
    {
        std::cerr << "Could not load image: " << filename << std::endl;
        return false;
    }

    // create texture from surface, texture is a friend class of renderer
    _texture = SDL_CreateTextureFromSurface(renderer._renderer, surface);
    // once texture is created, surface can be freed up
    SDL_FreeSurface(surface);
    if (!_texture)
    {
        std::cerr << "Could not create texture: " << filename << std::endl;
        return false;
    }

    return true;
}

bool Texture::Create(std::string name, ...)
{
    va_list args;
    va_start(args, name);
    Renderer& renderer = va_arg(args, Renderer);
    va_end(args);

    return Load(name, renderer);
}

Vector2 Texture::GetSize()
{
    ASSERT(_texture != nullptr);

    // query the texture for the size
    // https://wiki.libsdl.org/SDL2/SDL_QueryTexture
    SDL_Point size;
    SDL_QueryTexture(_texture, NULL, NULL, &size.x, &size.y);

    return Vector2{ size.x, size.y };
}
