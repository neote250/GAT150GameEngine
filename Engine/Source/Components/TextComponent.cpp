#include "TextComponent.h"
#include "Resource/ResourceManager.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"


FACTORY_REGISTER(TextComponent)

TextComponent::TextComponent(const TextComponent& other)
{
	text = other.text;
	fontName = other.fontName;
	fontSize = other.fontSize;
	color = other.color;

	textChanged = true;
	_text = std::make_unique<Text>(*other._text.get());
}

void TextComponent::Initialize()
{
	if (!_text && !fontName.empty())
	{
		auto font = ResourceManager::Instance().Get<Font>(fontName, fontSize);
		_text = std::make_unique<Text>(font);
	}
}

void TextComponent::Update(float dt)
{
}

void TextComponent::Draw(Renderer& renderer)
{
	//update text if changed
	if (textChanged) 
	{
		textChanged = false;
		_text->Create(renderer, text, color);
	}

	renderer.DrawTexture(_text->GetTexture(), owner->transform);
}

void TextComponent::SetText(const std::string& text)
{
	//check for new text
	if (this->text != text)
	{
		this->text = text;
		textChanged = true;
	}
}



void TextComponent::Read(const json_t& value)
{
	READ_DATA(value, text);
	READ_DATA(value, fontSize);
	READ_DATA(value, fontName);
	READ_DATA(value, color);
}

void TextComponent::Write(json_t& value)
{
}