#include "TextureAnimationComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Engine.h"

FACTORY_REGISTER(TextureAnimationComponent)

void TextureAnimationComponent::Initialize()
{
	TextureComponent::Initialize();
	// set textures for animations
	for (auto& animation : m_animations)
	{
		animation.second.texture = ResourceManager::Instance().Get<Texture>(animation.second.textureName, owner->scene->engine->GetRenderer());
	}

	// set default animation
	if (!animationName.empty()) SetAnimation(animationName, false);

	// update the source if not defined
	if (source.w == 0 && source.h == 0)
	{
		UpdateSource();
	}
	
}

void TextureAnimationComponent::Update(float dt)
{
	TextureComponent::Update(dt);

	// update timer
	frameTimer -= dt;
	if (frameTimer <= 0)
	{
		frameTimer = 1.0f / m_animation->fps;
		frame++;
		if (frame > m_animation->endFrame) frame = m_animation->startFrame;
	}

	UpdateSource();
}

void TextureAnimationComponent::SetAnimation(const std::string& name, bool update)
{
	// prevent setting animation again
	if (m_animation && IsEqualIgnoreCase(m_animation->name, name)) return;

	// find animation in animations
	if (m_animations.find(name) != m_animations.end())
	{
		// set new animation
		m_animation = &m_animations[name];

		// set texture
		if (m_animation->texture) texture = m_animation->texture;

		// reset frame information
		frame = m_animation->startFrame;
		frameTimer = 1.0f / m_animation->fps;

		if (update) UpdateSource();
	}
}

void TextureAnimationComponent::UpdateSource()
{
	// calculate subimage size
	Vector2 size = texture->GetSize() / Vector2{ m_animation->numColumns, m_animation->numRows };
	int column = (frame - 1) % m_animation->numColumns;
	int row = (frame - 1) / m_animation->numColumns;

	// set source rect from current column/row and subimage size
	source.x = (int)(column * size.x);
	source.y = (int)(row * size.y);
	source.w = (int)(size.x);
	source.h = (int)(size.y);
}

void TextureAnimationComponent::Read(const json_t& value)
{
	TextureComponent::Read(value);

	// read in animation sequences
	if (HAS_DATA(value, animations) && GET_DATA(value, animations).IsArray())
	{
		for (auto& animationValue : GET_DATA(value, animations).GetArray())
		{
			Animation animation;

			READ_DATA_NAME(animationValue, "name", animation.name);
			READ_DATA_NAME(animationValue, "fps", animation.fps);
			READ_DATA_NAME(animationValue, "numColumns", animation.numColumns);
			READ_DATA_NAME(animationValue, "numRows", animation.numRows);
			READ_DATA_NAME(animationValue, "startFrame", animation.startFrame);
			READ_DATA_NAME(animationValue, "endFrame", animation.endFrame);
			READ_DATA_NAME(animationValue, "textureName", animation.textureName);

			// add animation to animations
			m_animations[animation.name] = animation;
		}
	}

	READ_DATA(value, animationName);
}

void TextureAnimationComponent::Write(json_t& value)
{
	//
}
