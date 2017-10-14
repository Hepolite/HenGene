
#include "hen/ui/gui/Widget.h"

hen::gui::Widget::Widget(const std::string& name, Widget* parent)
	: m_name(name)
{
	m_family.setParent(parent);
	if (parent != nullptr)
		parent->m_family.addChild(this);

	setRender([this](const glm::vec2& pos, float dt)
	{
		for (auto& child : m_family.getChildren())
			child->onRender(pos, dt);
	});
}

void hen::gui::Widget::onProcess(float dt)
{
	m_pos.setPos(m_pos.getOffset() + m_link.getPos(*this));
	
	for (auto& child : m_family.getChildren())
		child->onProcess(dt);
	if (m_process != nullptr)
		m_process(dt);

	m_size.setSize(m_size.getMinSize(*this));
}
void hen::gui::Widget::onRender(const glm::vec2& pos, float dt) const
{
	if (m_render != nullptr && m_visible)
		m_render(pos, dt);
}

bool hen::gui::Widget::isVisible() const
{
	if (!m_visible)
		return false;
	return m_family.getParent() == nullptr ? true : m_family.getParent()->isVisible();
}
