#pragma once

#include <string>

#define CLASS_DECLARATION(class) \
	static const char* GetTypeName() { return #class; } //# means to get the string

class Object
{
public:
	Object() {}
	Object(const std::string& name) : name{ name } {}
	virtual ~Object() = default;

	virtual void Initialize() = 0;
	virtual void Activate() { active = true; }
	virtual void Deactivate() { active = false; }

public:
	std::string name;
	bool active{ false };

};
