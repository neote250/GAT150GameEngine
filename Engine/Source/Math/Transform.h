#pragma once

#include "Vector2.h"
#include "Core/Serializable.h"

struct Transform : public Serializable
{
	Vector2 position{ 0,0 };
	float rotation = 0;
	float scale = 1;

	Transform() {}
	Transform(Vector2 position, float rotation = 0, float scale = 1) : 
		position {position}
		,rotation {rotation}
		,scale {scale}
	{}

	Vector2 Forward() { return Vector2{ 1,0 }.Rotate(Math::DegToRad(rotation)); }

	// Inherited via Serializable
	void Read(const json_t& value) override;
	void Write(json_t& value) override;
};