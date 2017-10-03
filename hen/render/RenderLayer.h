
#pragma once

namespace hen
{
	namespace render
	{
		enum class RenderLayer
		{
			SCREEN,			// Allegro context
			INVISIBLE,		// Alpha == 0.0f
			OPAQUE,			// Alpha == 1.0f
			CUTOUT,			// Alpha == 0.0f || Alpha == 1.0f
			TRANSPARENT,	// Alpha >= 0.0f && Alpha < 1.0f
		};
	}
}