
#pragma once

#include "hen/io/File.h"
#include "hen/ui/gui/GuiResources.h"

namespace hen
{
	namespace gui
	{
		class Gui
		{
		public:
			Gui();
			Gui(const Gui&) = delete;
			Gui(Gui&&) = delete;
			~Gui();

			Gui& operator=(const Gui&) = delete;
			Gui& operator=(Gui&&) = delete;

			void onProcess(float dt);
			void onRender(float dt) const;
			void onLoad(const io::File& file);
			void onUnload();

			inline GuiResources& getResources() { return m_resources; }
			inline const GuiResources& getResources() const { return m_resources; }

			Widget* getWidget(const std::string& name);

		private:
			GuiResources m_resources;
		};
	}
}