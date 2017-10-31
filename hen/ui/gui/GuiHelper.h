
#pragma once

#include "hen/ui/gui/internal/GuiBase.h"
#include "hen/ui/gui/internal/GuiLayer.h"

#include "hen/io/File.h"

namespace hen
{
	namespace gui
	{
		void loadGuiFile(GuiBase& gui, const io::File& file);

		void loadMessageBox(GuiBase& gui, const std::string& message);
	}
}