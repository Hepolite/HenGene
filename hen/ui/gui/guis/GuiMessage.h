
#pragma once

#include "hen/ui/gui/guis/Gui.h"

#include <functional>

namespace hen
{
	namespace gui
	{
		class GuiMessage : protected Gui
		{
		public:
			virtual ~GuiMessage() = default;

			void open();
			inline void close() { Gui::close(); }

			void setMessage(const std::string& message);
			void setCallback(std::function<void()>&& callback);
		};
	}
}