
#pragma once

#include "hen/logic/script/Script.h"
#include "hen/ui/gui/Widget.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace hen
{
	namespace gui
	{
		class GuiResources
		{
		public:
			Widget& createWidget(const std::string& name, Widget* parent);
			Widget& getWidget(const std::string& name = "");
			bool hasWidget(const std::string& name = "") const;
			const Widget& getWidget(const std::string& name = "") const;
			std::vector<Widget*> getWidgets();
			
			inline script::Script& getScript() { return m_script; }
			inline const script::Script& getScript() const { return m_script; }

			inline void clear() { m_widgets.clear(); }

		private:
			std::unordered_map<std::string, Widget> m_widgets;

			script::Script m_script;
		};
	}
}
