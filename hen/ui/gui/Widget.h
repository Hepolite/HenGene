
#pragma once

#include "hen/ui/gui/components/ComponentAsset.h"
#include "hen/ui/gui/components/ComponentBorder.h"
#include "hen/ui/gui/components/ComponentClickable.h"
#include "hen/ui/gui/components/ComponentData.h"
#include "hen/ui/gui/components/ComponentFamily.h"
#include "hen/ui/gui/components/ComponentGroup.h"
#include "hen/ui/gui/components/ComponentLink.h"
#include "hen/ui/gui/components/ComponentListener.h"
#include "hen/ui/gui/components/ComponentPosition.h"
#include "hen/ui/gui/components/ComponentScript.h"
#include "hen/ui/gui/components/ComponentSize.h"

#include <glm/vec2.hpp>

#include <functional>
#include <string>

namespace hen
{
	namespace gui
	{
		class GuiResources;

		class Widget
		{
		public:
			Widget() = default;
			Widget(const std::string& name, Widget* parent);
			Widget(const Widget&) = delete;
			Widget(Widget&&) = delete;
			~Widget() = default;

			Widget& operator=(const Widget&) = delete;
			Widget& operator=(Widget&&) = delete;

			void onProcess(float dt);
			void onRender(const glm::vec2& offset, float dt) const;

			inline void setProcess(std::function<void(Widget&, float)>&& process) { m_process = process; }
			inline void setRender(std::function<void(const Widget&, const glm::vec2&, float)>&& render) { m_render = render; }

			inline std::string getName() const { return m_name; }
			inline GuiResources& getResources() { return *m_data.get<GuiResources*>(""); }
			inline const GuiResources& getResources() const { return *m_data.get<GuiResources*>(""); }

			inline void setVisible(bool visible) { m_visible = visible; }
			bool isVisible() const;

			inline void click() const { m_clickable.invoke(); }

			ComponentAsset m_asset;
			ComponentBorder m_border;
			ComponentClickable m_clickable;
			ComponentData m_data;
			ComponentFamily m_family;
			ComponentGroup m_group;
			ComponentLink m_link;
			ComponentListener m_listener;
			ComponentPosition m_pos;
			ComponentScript m_script;
			ComponentSize m_size;

		private:
			std::string m_name;
			bool m_visible = true;

			std::function<void(Widget&, float)> m_process;
			std::function<void(const Widget&, const glm::vec2&, float)> m_render;
		};
	}
}