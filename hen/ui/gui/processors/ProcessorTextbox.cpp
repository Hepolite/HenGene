
#include "hen/ui/gui/processors/ProcessorTextbox.h"

#include "hen/ui/gui/processors/ProcessorLabel.h"
#include "hen/ui/gui/processors/ProcessorPanel.h"

void hen::gui::ProcessorTextbox::operator()(const glm::vec2& offset, float dt) const
{
	const glm::vec2 border{ m_widget.m_border.getInnerLeft(), m_widget.m_border.getInnerTop() };
	ProcessorPanel{ m_widget }.operator()(offset, dt);
	ProcessorLabel{ m_widget }.operator()(offset + border, dt);
}
