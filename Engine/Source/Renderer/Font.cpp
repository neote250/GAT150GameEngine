
#include <iostream>
#include "Font.h"

Font::~Font()
{
	if (_ttfFont != nullptr)
	{
		TTF_CloseFont(_ttfFont);
	}
}

bool Font::Create(std::string name, ...)
{
	va_list args;
	va_start(args,name);
	int fontSize = va_arg(args, int);
	va_end(args);

	return Load(name, fontSize);
}

bool Font::Load(const std::string& name, int fontSize)
{
	_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
	if (_ttfFont == nullptr)
	{
		std::cerr << "Could not load font: " << name << std::endl;
		return false;
	}

	return true;
}