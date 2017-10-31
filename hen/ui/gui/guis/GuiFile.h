
#pragma once

#include "hen/ui/gui/guis/Gui.h"

#include <string>

namespace hen
{
	namespace gui
	{
		class GuiFile : public Gui
		{
		public:
			virtual ~GuiFile() = default;

			void load(const std::string& filepath);
		};
	}
}