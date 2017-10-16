
#include "hen/ui/gui/processors/ProcessorLabel.h"

#include "hen/ui/gui/Constants.h"
#include "hen/render/Text.h"

void hen::gui::ProcessorLabel::operator()(const glm::vec2& offset, float dt) const
{
	const auto text = m_widget.m_data.get<render::Text>(DATA_TEXT, render::Text{});
	const auto pos = m_widget.m_pos.getPos();

	text.render(pos + offset);
}
