
#pragma once

namespace hen
{
	namespace core
	{
		struct Settings
		{
			struct
			{
				int m_width = 640;
				int m_height = 480;
				bool m_fullscreen = false;
			} m_display;

			struct
			{
				double m_cps = 60.0;
				double m_fps = 60.0;
			} m_loop;
		};
	}
}