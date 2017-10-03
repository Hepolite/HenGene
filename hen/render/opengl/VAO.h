
#pragma once

namespace hen
{
	namespace opengl
	{
		class VAO
		{
		public:
			VAO();
			VAO(const VAO&) = delete;
			VAO(VAO&&) = delete;
			~VAO();

			VAO& operator=(const VAO&) = delete;
			VAO& operator=(VAO&&) = delete;

			bool bind() const;
			bool unbind() const;

			inline unsigned int getHandle() const { return m_handle; }

		private:
			static unsigned int m_boundHandle;

			unsigned int m_handle = 0;
		};
	}
}