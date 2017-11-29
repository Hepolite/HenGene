
#pragma once

#define NOMINMAX

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <algorithm>
#include <cmath>
#include <math.h>

namespace hen
{
	namespace math
	{
		const float PI = 3.141592653589793f;

		/* Returns the smallest value of the inputs, component wise */
		template<typename T>
		inline constexpr T min(const T& v1, const T& v2)
		{
			return std::min(v1, v2);
		}
		template<typename T>
		inline constexpr glm::tvec2<T> min(const glm::tvec2<T>& v1, const glm::tvec2<T>& v2)
		{
			return glm::tvec2<T>{ min(v1.x, v2.x), min(v1.y, v2.y) };
		}
		template<typename T>
		inline constexpr glm::tvec3<T> min(const glm::tvec3<T>& v1, const glm::tvec3<T>& v2)
		{
			return glm::tvec3<T>{ min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z) };
		}
		template<typename T>
		inline constexpr glm::tvec4<T> min(const glm::tvec4<T>& v1, const glm::tvec4<T>& v2)
		{
			return glm::tvec4<T>{ min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z), min(v1.w, v2.w) };
		}

		/* Returns the smallest component value of the input */
		template<typename T>
		inline constexpr T min(const glm::tvec2<T>& v)
		{
			return std::min(v.x, v.y);
		}
		template<typename T>
		inline constexpr T min(const glm::tvec3<T>& v)
		{
			return std::min(v.x, v.y, v.z);
		}
		template<typename T>
		inline constexpr T min(const glm::tvec4<T>& v)
		{
			return std::min(v.x, v.y, v.z, v.w);
		}

		/* Returns the largest value of the inputs, component wise */
		template<typename T>
		inline constexpr T max(const T& v1, const T& v2)
		{
			return std::max(v1, v2);
		}
		template<typename T>
		inline constexpr glm::tvec2<T> max(const glm::tvec2<T>& v1, const glm::tvec2<T>& v2)
		{
			return glm::tvec2<T>{ max(v1.x, v2.x), max(v1.y, v2.y) };
		}
		template<typename T>
		inline constexpr glm::tvec3<T> max(const glm::tvec3<T>& v1, const glm::tvec3<T>& v2)
		{
			return glm::tvec3<T>{ max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z) };
		}
		template<typename T>
		inline constexpr glm::tvec4<T> max(const glm::tvec4<T>& v1, const glm::tvec4<T>& v2)
		{
			return glm::tvec4<T>{ max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z), max(v1.w, v2.w) };
		}

		/* Returns the largest component value of the input */
		template<typename T>
		inline constexpr T max(const glm::tvec2<T>& v)
		{
			return std::max(v.x, v.y);
		}
		template<typename T>
		inline constexpr T max(const glm::tvec3<T>& v)
		{
			return std::max(v.x, v.y, v.z);
		}
		template<typename T>
		inline constexpr T max(const glm::tvec4<T>& v)
		{
			return std::max(v.x, v.y, v.z, v.w);
		}

		/* Returns a vector where all elements is -1, 0 or 1, depending on the sign of the vector elements */
		template<typename T>
		inline constexpr int sign(const T& v)
		{
			return (T{ 0 } < v) - (v < T{ 0 });
		}
		template<typename T>
		inline constexpr glm::ivec2 sign(const glm::tvec2<T>& v)
		{
			return glm::ivec2{ sign(v.x), sign(v.y) };
		}
		template<typename T>
		inline constexpr glm::ivec3 sign(const glm::tvec3<T>& v)
		{
			return glm::ivec3{ sign(v.x), sign(v.y), sign(v.z) };
		}
		template<typename T>
		inline constexpr glm::ivec4 sign(const glm::tvec4<T>& v)
		{
			return glm::ivec4{ sign(v.x), sign(v.y), sign(v.z), sign(v.w) };
		}

		/* Returns a vector where all elements are the abolute value of the input elements */
		template<typename T>
		inline constexpr T abs(const T& v)
		{
			return std::abs(v);
		}
		template<typename T>
		inline constexpr glm::tvec2<T> abs(const glm::tvec2<T>& v)
		{
			return glm::tvec2<T>{ abs(v.x), abs(v.y) };
		}
		template<typename T>
		inline constexpr glm::tvec3<T> abs(const glm::tvec3<T>& v)
		{
			return glm::tvec3<T>{ abs(v.x), abs(v.y), abs(v.z) };
		}
		template<typename T>
		inline constexpr glm::tvec4<T> abs(const glm::tvec4<T>& v)
		{
			return glm::tvec4<T>{ abs(v.x), abs(v.y), abs(v.z), abs(v.w) };
		}

		/* Returns a vector where all elements has been rounded down towards negative infinity */
		template<typename T>
		inline constexpr int floor(const T& v)
		{
			return static_cast<int>(std::floor(v));
		}
		template<typename T>
		inline constexpr glm::ivec2 floor(const glm::tvec2<T>& v)
		{
			return glm::ivec2{ floor(v.x), floor(v.y) };
		}
		template<typename T>
		inline constexpr glm::ivec3 floor(const glm::tvec3<T>& v)
		{
			return glm::ivec3{ floor(v.x), floor(v.y), floor(v.z) };
		}
		template<typename T>
		inline constexpr glm::ivec4 floor(const glm::tvec4<T>& v)
		{
			return glm::ivec4{ floor(v.x), floor(v.y), floor(v.z), floor(v.w) };
		}

		/* Returns a vector where all elements has been rounded towards the nearest whole integer */
		template<typename T>
		inline constexpr int round(const T& v)
		{
			return static_cast<int>(std::round(v));
		}
		template<typename T>
		inline constexpr glm::ivec2 round(const glm::tvec2<T>& v)
		{
			return glm::ivec2{ round(v.x), round(v.y) };
		}
		template<typename T>
		inline constexpr glm::ivec3 round(const glm::tvec3<T>& v)
		{
			return glm::ivec3{ round(v.x), round(v.y), round(v.z) };
		}
		template<typename T>
		inline constexpr glm::ivec4 round(const glm::tvec4<T>& v)
		{
			return glm::ivec4{ round(v.x), round(v.y), round(v.z), round(v.w) };
		}

		/* Returns a vector where all elements has been rounded down towards positive infinity */
		template<typename T>
		inline constexpr int ceil(const T& v)
		{
			return static_cast<int>(std::ceil(v));
		}
		template<typename T>
		inline constexpr glm::ivec2 ceil(const glm::tvec2<T>& v)
		{
			return glm::ivec2{ ceil(v.x), ceil(v.y) };
		}
		template<typename T>
		inline constexpr glm::ivec3 ceil(const glm::tvec3<T>& v)
		{
			return glm::ivec3{ ceil(v.x), ceil(v.y), ceil(v.z) };
		}
		template<typename T>
		inline constexpr glm::ivec4 ceil(const glm::tvec4<T>& v)
		{
			return glm::ivec4{ ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w) };
		}

		/* Returns a vector where all elements has raised to the given power */
		template<typename T, typename P>
		inline constexpr T pow(const T& v, const P& p)
		{
			return static_cast<T>(std::pow(v, p));
		}
		template<typename T, typename P>
		inline constexpr glm::tvec2<T> pow(const glm::tvec2<T>& v, const P& p)
		{
			return glm::tvec2<T>{ pow(v.x, p), pow(v.y, p) };
		}
		template<typename T, typename P>
		inline constexpr glm::tvec3<T> pow(const glm::tvec3<T>& v, const P& p)
		{
			return glm::tvec3<T>{ pow(v.x, p), pow(v.y, p), pow(v.z, p) };
		}
		template<typename T, typename P>
		inline constexpr glm::tvec4<T> pow(const glm::tvec4<T>& v, const P& p)
		{
			return glm::tvec4<T>{ pow(v.x, p), pow(v.y, p), pow(v.z, p), pow(v.w, p) };
		}


		/* Returns a linearly interpolated value between the two bounds, given as v1 * (1 - dt) + v2 * dt */
		template<typename T, typename P>
		inline constexpr T lerp(const T& v1, const T& v2, const P& dt) { return v1 * (P{ 1 } - dt) + v2 * dt; }


		/* Returns the squared length of the vector */
		template<typename T>
		inline constexpr T lengthSquared(const glm::tvec2<T>& v) { return v.x * v.x + v.y * v.y; }
		template<typename T>
		inline constexpr T lengthSquared(const glm::tvec3<T>& v) { return v.x * v.x + v.y * v.y + v.z * v.z; }
		template<typename T>
		inline constexpr T lengthSquared(const glm::tvec4<T>& v) { return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w; }



		/* Finds the smallest number t such that s + t*ds is an integer */
		template<typename T>
		inline float intbound(const T& s, const T& ds)
		{
			return (ds > T{ 0 } ? ceil(s) - s : s - floor(s)) / abs(ds);
		}
		template<typename T>
		inline constexpr glm::vec2 intbound(const glm::tvec2<T>& s, const glm::tvec2<T>& ds)
		{
			return glm::vec2{ intbound(s.x, ds.x), intbound(s.y, ds.y) };
		}
		template<typename T>
		inline constexpr glm::vec3 intbound(const glm::tvec3<T>& s, const glm::tvec3<T>& ds)
		{
			return glm::vec3{ intbound(s.x, ds.x), intbound(s.y, ds.y), intbound(s.z, ds.z) };
		}
		template<typename T>
		inline constexpr glm::vec4 intbound(const glm::tvec4<T>& s, const glm::tvec4<T>& ds)
		{
			return glm::vec4{ intbound(s.x, ds.x), intbound(s.y, ds.y), intbound(s.z, ds.z), intbound(s.w, ds.w) };
		}



		/* Returns the angle between the two vectors, A = arccos(v1*v2 / |v1||v2|) */
		float getAngle(glm::vec3 v1, glm::vec3 v2);

		/* Converts a direction to a cartesian form */
		glm::vec3 toCartesian(float yaw, float pitch);
		/* Converts a direction on the form (yaw, pitch) to a cartesian form */
		inline glm::vec3 toCartesian(const glm::vec2& rotation) { return toCartesian(rotation.x, rotation.y); }
		/* Converts a direction on the form (yaw, pitch, roll) to a cartesian form */
		inline glm::vec3 toCartesian(const glm::vec3& rotation) { return toCartesian(rotation.x, rotation.y); }

		/* Converts a vector on the form x, y, z to the spherical form (yaw, pitch) */
		glm::vec2 toSpherical(const glm::vec3& vector);
		/* Converts a vector on the form x, y, z to the spherical form (yaw, pitch) */
		inline glm::vec2 toSpherical(float x, float y, float z) { return toSpherical(glm::vec3(x, y, z)); }
	}
}
