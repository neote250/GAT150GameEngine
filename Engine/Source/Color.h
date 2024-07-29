#pragma once

#include "MathUtils.h"
#include <cmath>
#include <stdint.h>

struct Color {
	float r;
	float g;
	float b;
	float a;

	Color() = default;
	Color(float r, float g, float b, float a=0) 
	{ this->r = r; this->g = g; this->b = b; this->a = a;};

	float operator [] (unsigned int index) const { return (&r)[index]; }
	float& operator [] (unsigned int index) { return (&r)[index]; }

	Color operator + (const Color& v) const { return Color{ r + v.r, g + v.g, b + v.b, a + v.a }; }
	Color operator - (const Color& v) const { return Color{ r - v.r, g - v.g, b - v.b, a - v.a }; }
	Color operator * (const Color& v) const { return Color{ r * v.r, g * v.g, b * v.b, a * v.a }; }
	Color operator / (const Color& v) const { return Color{ r / v.r, g / v.g, b / v.b, a / v.a }; }

	Color operator + (float s) const { return Color(r + s, g + s, b + s, a + s); }
	Color operator - (float s) const { return Color(r - s, g - s, b - s, a - s); }
	Color operator * (float s) const { return Color(r * s, g * s, b * s, a * s); }
	Color operator / (float s) const { return Color(r / s, g / s, b / s, a / s); }

	Color& operator += (const Color& v) { r += v.r; g += v.g; b += v.b; a += v.a; return *this;}
	Color& operator -= (const Color& v) { r -= v.r; g -= v.g; b -= v.b; a -= v.a; return *this; }
	Color& operator *= (const Color& v) { r *= v.r; g *= v.g; b *= v.b; a *= v.a; return *this; }
	Color& operator /= (const Color& v) { r /= v.r; g /= v.g; b /= v.b; a /= v.a; return *this; }

	Color& operator += (float s) { r += s; g += s, b += s; a += s; return *this;}
	Color& operator -= (float s) { r -= s; g -= s, b -= s; a -= s; return *this; }
	Color& operator *= (float s) { r *= s; g *= s, b *= s; a *= s; return *this; }
	Color& operator /= (float s) { r /= s; g /= s, b /= s; a /= s; return *this; }

	static uint8_t ToInt(float v) { return static_cast<uint8_t>(Math::Clamp(v,0.0f,1.0f) * 255);  }
};
