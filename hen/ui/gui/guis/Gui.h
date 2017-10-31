
#pragma once

#include "hen/ui/gui/internal/GuiBase.h"
#include "hen/ui/gui/internal/GuiLayer.h"

namespace hen
{
	namespace gui
	{
		class Gui
		{
		public:
			Gui() = default;
			Gui(const Gui&) = delete;
			Gui(Gui&&) = delete;
			virtual ~Gui() = default;

			Gui& operator=(const Gui&) = delete;
			Gui& operator=(Gui&&) = delete;

			void open(GuiLayer layer = GuiLayer::NORMAL_PRIORITY);
			void close();
			void load(const std::string& filepath);

			script::Script& getScript();

		protected:
			inline GuiBase* getHandle() const { return m_handle; }

		private:
			GuiBase* m_handle = nullptr;
		};
	}
}