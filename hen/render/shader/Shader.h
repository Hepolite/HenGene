
#pragma once

#include "hen/io/File.h"
#include "hen/render/shader/ShaderType.h"

#include <string>

namespace hen
{
	namespace shader
	{
		class Shader
		{
		public:
			Shader() = default;
			Shader(ShaderType type, const io::File& file);
			Shader(const Shader&) = delete;
			Shader(Shader&&) = delete;
			~Shader();

			Shader& operator=(const Shader&) = delete;
			Shader& operator=(Shader&&) = delete;

			inline unsigned int getHandle() const { return m_handle; }

		private:
			std::string parse(const io::File& file) const;
			bool compile(const std::string& code) const;

			unsigned int m_handle = 0;
		};
	}
}