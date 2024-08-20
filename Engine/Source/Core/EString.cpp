#include "EString.h"

std::string ToLower(const std::string& str)
{
	std::string lowerStr;
	lowerStr.resize(str.size());

	//c/c++
	for (int i = 0; i < str.size(); i++)
	{
		lowerStr[i] = std::tolower(str[i]);
	}
	//modern c++ (algorithms)
	//std::transform(str.begin(), str.end(), lowerStr.begin(),
	//	[](char c)//anonymous function, aka function without a name
	//	{
	//		return std::tolower(c);
	//	});

	return lowerStr;
}

std::string ToUpper(const std::string& str)
{
	std::string upperStr;
	upperStr.resize(str.size());

	//c/c++
	for (int i = 0; i < str.size(); i++)
	{
		upperStr[i] = std::toupper(str[i]);
	}
	return upperStr;
}

bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2)
{
	if (str1.length() != str2.length()) return false;

	//modern c++
	return std::equal(str1.begin(), str1.end(), str2.begin(),
		[](char c1, char c2)
		{
			return std::tolower(c1) == std::tolower(c2);
		});
}
