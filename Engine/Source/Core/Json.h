#pragma once

#include "Math/Vector2.h"
#include "Renderer/Color.h"
#include "Math/Rect.h"

#include <vector>
#include <string>
#include <rapidjson/document.h>

#define READ_DATA(value, data)					Json::Read(value, #data, data)
#define READ_DATA_REQUIRED(value,data)			Json::Read(value, #data, data, true)
#define READ_DATA_NAME(value, name, data)		Json::Read(value, name, data)
#define READ_DATA_STRUCT(value, data, _struct)	Json::Read(value, #data, _struct.##data)//## appends 2 things together?

#define HAS_DATA(value,data)					value.HasMember(#data)
#define GET_DATA(value, data)					value[#data]


namespace Json
{
	bool Load(const std::string& filename, rapidjson::Document& document);
	bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, struct Vector2& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, struct Color& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, struct Rect& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, std::vector<int>& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data, bool isRequired = false);
}

using json_t = rapidjson::Value;