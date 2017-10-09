
#include "hen/util/StringLib.h"

#include <sstream>
#include <iterator>

namespace
{
	template<typename T>
	std::vector<T> as_T_array(const std::string& string)
	{
		// Can't explain this? Me neither... Somehow converts the string into a vector of type T
		return{ std::istream_iterator<T>{ std::istringstream{ string } },{} };
	}
}

int hen::string::as_int(const std::string& string, int def)
{
	try { return std::stoi(string); }
	catch (...) {}
	return def;
}
float hen::string::as_float(const std::string& string, float def)
{
	try { return std::stof(string); }
	catch (...) {}
	return def;
}

std::vector<int> hen::string::as_int_vector(const std::string& string)
{
	return as_T_array<int>(string);
}
std::vector<unsigned int> hen::string::as_uint_vector(const std::string & string)
{
	return as_T_array<unsigned int>(string);
}
std::vector<float> hen::string::as_float_vector(const std::string& string)
{
	return as_T_array<float>(string);
}
std::vector<std::string> hen::string::as_string_vector(const std::string& string)
{
	return as_T_array<std::string>(string);
}

glm::vec2 hen::string::as_vec2(const std::string& string)
{
	auto data = as_T_array<float>(string);
	return data.size() == 2 ? glm::vec2{ data[0], data[1] } : glm::vec2{};
}
glm::ivec2 hen::string::as_ivec2(const std::string& string)
{
	auto data = as_T_array<int>(string);
	return data.size() == 2 ? glm::ivec2{ data[0], data[1] } : glm::ivec2{};
}
glm::uvec2 hen::string::as_uvec2(const std::string& string)
{
	auto data = as_T_array<unsigned int>(string);
	return data.size() == 2 ? glm::uvec2{ data[0], data[1] } : glm::uvec2{};
}
glm::vec3 hen::string::as_vec3(const std::string& string)
{
	auto data = as_T_array<float>(string);
	return data.size() == 3 ? glm::vec3{ data[0], data[1], data[2] } : glm::vec3{};
}
glm::ivec3 hen::string::as_ivec3(const std::string& string)
{
	auto data = as_T_array<int>(string);
	return data.size() == 3 ? glm::ivec3{ data[0], data[1], data[2] } : glm::ivec3{};
}
glm::uvec3 hen::string::as_uvec3(const std::string& string)
{
	auto data = as_T_array<unsigned int>(string);
	return data.size() == 3 ? glm::uvec3{ data[0], data[1], data[2] } : glm::uvec3{};
}
glm::vec4 hen::string::as_vec4(const std::string& string)
{
	auto data = as_T_array<float>(string);
	return data.size() == 4 ? glm::vec4{ data[0], data[1], data[2], data[3] } : glm::vec4{};
}
glm::ivec4 hen::string::as_ivec4(const std::string& string)
{
	auto data = as_T_array<int>(string);
	return data.size() == 4 ? glm::ivec4{ data[0], data[1], data[2], data[3] } : glm::ivec4{};
}
glm::uvec4 hen::string::as_uvec4(const std::string& string)
{
	auto data = as_T_array<unsigned int>(string);
	return data.size() == 4 ? glm::uvec4{ data[0], data[1], data[2], data[3] } : glm::uvec4{};
}
ALLEGRO_COLOR hen::string::as_color(const std::string& string)
{
	auto data = as_T_array<float>(string);
	switch (data.size())
	{
	case 4:
		return ALLEGRO_COLOR{ data[0], data[1], data[2], data[3] };
	case 3:
		return ALLEGRO_COLOR{ data[0], data[1], data[2], 1.0f };
	case 2:
		return ALLEGRO_COLOR{ data[0], data[0], data[0], data[1] };
	case 1:
		return ALLEGRO_COLOR{ data[0], data[0], data[0], 1.0f };
	default:
		return ALLEGRO_COLOR{ 1.0f, 1.0f, 1.0f, 1.0f };
	}
}

std::string hen::string::replace_all(const std::string& string, const std::string& sub, const std::string& rep)
{
	if (string.length() < sub.length())
		return string;

	const std::size_t subSize = sub.length();
	const std::size_t repSize = rep.length();
	std::string newString = string;

	for (std::size_t pos = 0; ; pos += repSize)
	{
		pos = newString.find(sub, pos);
		if (pos == std::string::npos)
			break;
		if (subSize == repSize)
			newString.replace(pos, subSize, rep);
		else
		{
			newString.erase(pos, subSize);
			newString.insert(pos, rep);
		}
	}
	return newString;
}
std::vector<std::string> hen::string::split(const std::string& string, const char delim)
{
	std::vector<std::string> elements;
	std::stringstream stream{ string };
	std::string item;
	auto out = std::back_inserter(elements);
	while (std::getline(stream, item, delim))
		*(out++) = item;
	return elements;
}
