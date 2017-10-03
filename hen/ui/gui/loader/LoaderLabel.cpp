
#include "hen/ui/gui/loader/LoaderLabel.h"

void hen::gui::LoaderLabel::render(const Widget& widget, const glm::vec2& offset, float dt)
{
	const auto pos = widget.m_pos.getPos();
	widget.m_data.get<render::Text>("text", render::Text{}).render(pos + offset);
}

//////////////////////////////////////////////////////////////////////////

void hen::gui::LoaderLabel::load(Widget& widget, const pugi::xml_node& node) const
{
	widget.setRender(&LoaderLabel::render);

	loadText(widget, node.child("text"));
}
void hen::gui::LoaderLabel::loadText(Widget& widget, const pugi::xml_node& node) const
{
	render::Text text;

	if (const auto& attribute = node.attribute("font"))
		text.setFont(widget.m_asset.addFont(attribute.as_string()));
	if (const auto& attribute = node.attribute("align"))
	{
		const std::string alignment = attribute.as_string("left");
		if (alignment == "left")
			text.setAlign(render::Text::Align::LEFT);
		else if (alignment == "center")
			text.setAlign(render::Text::Align::CENTER);
		else if (alignment == "right")
			text.setAlign(render::Text::Align::RIGHT);
	}
	if (const auto& attribute = node.attribute("height"))
		text.setLineHeight(attribute.as_float());
	if (const auto& attribute = node.attribute("width"))
		text.setMaxWidth(attribute.as_float());

	text.setText(node.child_value());
	setText(widget, text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void hen::gui::LoaderLabel::setText(Widget& widget, const render::Text& text)
{
	widget.m_data.set<render::Text>("text", text);
	widget.m_size.setMinSize(text.getSize());
}