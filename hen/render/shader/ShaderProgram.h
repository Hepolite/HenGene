
#pragma once

#include "hen/io/File.h"
#include "hen/render/shader/ShaderType.h"

namespace hen
{
	namespace shader
	{
		class ShaderProgram
		{
		public:
			ShaderProgram();
			ShaderProgram(const ShaderProgram&) = delete;
			ShaderProgram(ShaderProgram&&) = delete;
			~ShaderProgram();

			ShaderProgram& operator=(const ShaderProgram&) = delete;
			ShaderProgram& operator=(ShaderProgram&&) = delete;

			void onLoad(const io::File& file);
			void onUnload();

			bool attach(ShaderType type, const io::File& file);
			bool build();

			void bind() const;

			inline bool isBuilt() const { return m_isBuilt; }
			inline unsigned int getHandle() const { return m_handle; }
			static inline unsigned int getBoundHandle() { return m_boundHandle; }

		private:
			static unsigned int m_boundHandle;

			unsigned int m_handle = 0;
			bool m_isBuilt = false;
			std::string m_path;
		};
	}
}