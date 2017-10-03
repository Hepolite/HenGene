
#pragma once

#include <vector>

namespace hen
{
	namespace gui
	{
		class Widget;

		class ComponentFamily
		{
		public:
			inline void setParent(Widget* parent) { m_parent = parent; }
			inline void addChild(Widget* child) { m_children.push_back(child); }

			inline const Widget* getParent() const { return m_parent; }
			inline const std::vector<Widget*>& getChildren() const { return m_children; }

		private:
			Widget* m_parent = nullptr;
			std::vector<Widget*> m_children;
		};
	}
}