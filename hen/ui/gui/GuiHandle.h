
#pragma once

#include "hen/ui/gui/GuiLayer.h"

#include <string>

namespace hen
{
	namespace gui
	{
		struct GuiHandle
		{
			GuiHandle() : m_path(""), m_layer(GuiLayer::NORMAL_PRIORITY) {}
			GuiHandle(const std::string& path, GuiLayer layer) : m_path(path), m_layer(layer) {}

			const std::string m_path;
			const GuiLayer m_layer;
		};
	}
}