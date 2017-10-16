
#include "hen/ui/gui/loader/LoaderLabel.h"

#include "hen/ui/gui/Constants.h"
#include "hen/ui/gui/processors/ProcessorLabel.h"

#include <Log.h>

void hen::gui::LoaderLabel::load(const pugi::xml_node& node) const
{
	ProcessorLabel processor{ m_widget };
	m_widget.setRender(processor);

	loadText(node.child("text"));
}
void hen::gui::LoaderLabel::loadText(const pugi::xml_node& node) const
{
	const std::string attrAlign = node.attribute(ATTRIBUTE_TEXT_ALIGN).as_string(TEXT_ALIGN_LEFT.c_str());
	const std::string attrFont = node.attribute(ATTRIBUTE_TEXT_FONT).as_string();
	const std::string attrText = node.child_value();
	const auto attrHeight = node.attribute(ATTRIBUTE_TEXT_HEIGHT).as_float();
	const auto attrWidth = node.attribute(ATTRIBUTE_TEXT_WIDTH).as_float();

	render::Text text;

	if (!attrFont.empty())
		text.setFont(m_widget.m_asset.addFont(attrFont));
	
	if (attrAlign == "left")
		text.setAlign(render::Text::Align::LEFT);
	else if (attrAlign == "center")
		text.setAlign(render::Text::Align::CENTER);
	else if (attrAlign == "right")
		text.setAlign(render::Text::Align::RIGHT);
	else
		LOG_WARNING << "Unknown text aligment in widget " << m_widget.getName();
	
	if (attrHeight != 0.0f)
		text.setLineHeight(attrHeight);
	if (attrWidth != 0.0f)
		text.setMaxWidth(attrWidth);

	text.setText(attrText);

	m_widget.m_data.set<render::Text>("text", text);
	m_widget.m_size.setMinSize(text.getSize());
}
