
#include "hen/ui/gui/loader/LoaderTextfield.h"

#include "hen/core/Core.h"
#include "hen/ui/gui/internal/GuiResources.h"
#include "hen/ui/gui/loader/LoaderButton.h"
#include "hen/ui/Keyboard.h"

void hen::gui::LoaderTextfield::process(Widget& widget, float dt)
{
	if (!widget.m_clickable.isClicked())
		return;

	const auto& keyboard = Core::getKeyboard();

	if (keyboard.isPressed(ALLEGRO_KEY_ESCAPE) || keyboard.isPressed(ALLEGRO_KEY_ENTER))
	{
		widget.m_clickable.setClicked(false);
		widget.m_clickable.invoke();
	}
	else if (keyboard.isHeld(ALLEGRO_KEY_BACKSPACE))
	{
		const auto value = getValue(widget);
		if (!value.empty())
		{
			setValue(widget, value.substr(0, value.size() - 1));
			widget.m_clickable.invoke();
		}
	}
	else if (!keyboard.getCharacters().empty())
	{
		setValue(widget, getValue(widget) + keyboard.getCharacters());
		widget.m_clickable.invoke();
	}
}
void hen::gui::LoaderTextfield::render(const Widget& widget, const glm::vec2& offset, float dt)
{
	getText(widget).render(widget.m_pos.getPos() + offset);
}


void hen::gui::LoaderTextfield::load(Widget& widget, const pugi::xml_node& node) const
{
	//widget.setProcess(&process);
	//widget.setRender(&render);

	loadText(widget, node.child("text"));
	loadButton(widget, node.child("button"));

	widget.m_clickable.setInvoker([&]()
	{
		const auto& script = widget.m_script.get("change");
		if (!script.empty())
			widget.getResources().getScript().executeScript(script + "(\"" + getValue(widget) + "\")");
	});
}
void hen::gui::LoaderTextfield::loadText(Widget& widget, const pugi::xml_node& node) const
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
void hen::gui::LoaderTextfield::loadButton(Widget & widget, const pugi::xml_node & node) const
{
	auto& resources = widget.getResources();
	auto& button = resources.createWidget(widget.getName() + "_BUTTON", &widget);

	LoaderButton{ button }.load(pugi::xml_node{});

	button.m_size.setMinSize(widget.m_size.getMinSize());
	button.m_size.setMaxSize(widget.m_size.getMinSize());
	button.m_link.setTarget(&widget);
	button.m_link.setLocation(ComponentLink::Location::TOP_LEFT);
	button.m_clickable.setInvoker([&]() { widget.m_clickable.setClicked(true); });
}

hen::render::Text hen::gui::LoaderTextfield::getText(const Widget& widget)
{
	return widget.m_data.get<render::Text>("value", render::Text{});
}
void hen::gui::LoaderTextfield::setText(Widget& widget, const render::Text& text)
{
	widget.m_data.set("value", text);
}
std::string hen::gui::LoaderTextfield::getValue(const Widget& widget)
{
	return getText(widget).getText();
}
void hen::gui::LoaderTextfield::setValue(Widget& widget, const std::string& text)
{
	auto t = getText(widget);
	t.setText(text);
	setText(widget, t);
}
