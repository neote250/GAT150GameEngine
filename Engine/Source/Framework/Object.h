#pragma once
#include "Core/Serializable.h"
#include "Core/Factory.h"
#include <string>

#define CLASS_DECLARATION(classname) \
	static const char* GetTypeName() { return #classname; } \
	virtual void Read(const json_t& value); \
	virtual void Write(json_t& value);

#define FACTORY_REGISTER(classname) \
	class Register##classname		\
	{								\
	public:							\
		Register##classname()		\
		{							\
			Factory::Instance().Register<classname>(#classname);\
		}							\
	};								\
	static Register##classname register_instance;

#define CLASS_PROTOTYPE(classname)	\
	virtual std::unique_ptr<Object> Clone(){\
		return std::make_unique<classname>(*this);\
	}


class Object : public Serializable
{
public:
	Object() {}
	Object(const std::string& name) : name{ name } {}
	virtual ~Object() = default;

	virtual std::unique_ptr<Object> Clone() = 0;

	CLASS_DECLARATION(Object)

	virtual void Initialize() = 0;
	virtual void Activate() { active = true; }
	virtual void Deactivate() { active = false; }

public:
	std::string name;
	bool active{ true };
	bool persistent{ false };
};
