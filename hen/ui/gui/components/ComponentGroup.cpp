
#include "ComponentGroup.h"

#include "hen/ui/gui/Widget.h"

void hen::gui::ComponentGroup::add(Widget* member)
{
	if (member == nullptr)
		return;
	
	if (member->m_group.m_leader != this)
	{
		for (auto& m : member->m_group.m_members)
			m_leader->m_members.push_back(m);
		member->m_group.m_leader = this;
		member->m_group.m_members.clear();
	}
	else
		m_leader->m_members.push_back(member);
}
