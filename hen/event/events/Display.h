
#pragma once

namespace hen
{
	namespace events
	{
		class DisplayClose
		{};

		class DisplayResize
		{
		public:
			DisplayResize(int width, int height) : m_width(width), m_height(height) {}

			inline int getWidth() const { return m_width; }
			inline int getHeight() const { return m_height; }

		private:
			int m_width;
			int m_height;
		};
	}
}