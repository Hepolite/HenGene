
#pragma once

#include <allegro5/color.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <string>
#include <vector>

namespace hen
{
	namespace string
	{
		std::string replace_all(const std::string& string, const std::string& sub, const std::string& rep);
		std::vector<std::string> split(const std::string& string, const char delim);

		int as_int(const std::string& string, int def = 0);
		float as_float(const std::string& string, float def = 0.0f);

		std::vector<int> as_int_vector(const std::string& string);
		std::vector<unsigned int> as_uint_vector(const std::string& string);
		std::vector<float> as_float_vector(const std::string& string);
		std::vector<std::string> as_string_vector(const std::string& string);

		glm::vec2 as_vec2(const std::string& string);
		glm::ivec2 as_ivec2(const std::string& string);
		glm::uvec2 as_uvec2(const std::string& string);
		glm::vec3 as_vec3(const std::string& string);
		glm::ivec3 as_ivec3(const std::string& string);
		glm::uvec3 as_uvec3(const std::string& string);
		glm::vec4 as_vec4(const std::string& string);
		glm::ivec4 as_ivec4(const std::string& string);
		glm::uvec4 as_uvec4(const std::string& string);
		ALLEGRO_COLOR as_color(const std::string& string);
	}
}