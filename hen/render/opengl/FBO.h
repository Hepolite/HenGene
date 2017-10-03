
#pragma once

namespace hen
{
	namespace opengl
	{
		class FBO
		{
		public:
			FBO();
			FBO(const FBO&) = delete;
			FBO(FBO&&) = delete;
			~FBO();

			FBO& operator=(const FBO&) = delete;
			FBO& operator=(FBO&&) = delete;

			bool bind() const;
			bool unbind() const;

			inline unsigned int getHandle() const { return m_handle; }

		private:
			static unsigned int m_boundHandle;

			unsigned int m_handle = 0;
		};
	}
}