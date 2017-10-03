
#pragma once

#include <vector>

namespace hen
{
	namespace gui
	{
		class Widget;

		class ComponentGroup
		{
		public:
			void add(Widget* member);
			inline const std::vector<Widget*>& getMembers() const { return m_leader->m_members; }

		private:
			ComponentGroup* m_leader = this;
			std::vector<Widget*> m_members;
		};
	}
}