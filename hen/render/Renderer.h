
#pragma once

#include "hen/render/RenderLayer.h"

#include <functional>

namespace hen
{
	namespace render
	{
		struct Renderer
		{
			Renderer() {}
			Renderer(RenderLayer layer, unsigned int index)
				: m_layer(layer), m_index(index)
			{}

			RenderLayer m_layer = RenderLayer::OPAQUE;
			unsigned int m_index = 0;
		};
	}
}