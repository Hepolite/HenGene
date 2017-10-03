
#include "hen/ui/gui/loader/Loader.h"

#include "hen/core/Core.h"
#include "hen/io/XMLFile.h"
#include "hen/ui/Display.h"
#include "hen/ui/gui/GuiResources.h"
#include "hen/ui/gui/loader/LoaderButton.h"
#include "hen/ui/gui/loader/LoaderLabel.h"
#include "hen/ui/gui/loader/LoaderPanel.h"
#include "hen/ui/gui/loader/LoaderSlider.h"
#include "hen/ui/gui/loader/LoaderWindow.h"
#include "hen/util/StringLib.h"

#include <Log.h>

namespace
{
	template<class Loader>
	inline void doLoad(hen::gui::Widget& widget, const pugi::xml_node& node)
	{
		Loader loader;
		loader.load(widget, node);
	}
}

void hen::gui::Loader::load(Gui& gui, const io::File& file) const
{
	m_path = file.getPath();
	io::XMLFile f{ file };
	const auto& doc = f.open();

	if (const auto& script = doc.child("script"))
	{
		if (const auto& scriptFile = script.attribute("file"))
			gui.getResources().getScript().executeFile(scriptFile.as_string());
		else
			gui.getResources().getScript().executeScript(script.child_value());
	}

	if (const auto& layout = doc.child("layout"))
	{
		auto& display = hen::Core::getDisplay();
		auto& widget = gui.getResources().createWidget("", nullptr);
		widget.m_size.setMaxSize(glm::vec2{ display.getWidth(), display.getHeight() });
		widget.m_size.setMinSize(widget.m_size.getMaxSize());
		loadFamily(widget, layout);
	}

	for (auto& widget : m_actives)
		widget->click();
	m_actives.clear();
}

void hen::gui::Loader::load(Widget& widget, const pugi::xml_node& node) const
{
	widget.setVisible(node.attribute("visible").as_bool(true));

	if (const auto& sprite = node.child("sprite"))
		loadAsset(widget, sprite);
	if (const auto& border = node.child("border"))
		loadBorder(widget, border);
	widget.m_group.add(&widget);
	if (const auto& group = node.child("group"))
		loadGroup(widget, group);
	if (const auto& link = node.child("link"))
		loadLink(widget, link);
	else
		widget.m_link.setTarget(widget.m_family.getParent());
	if (const auto& position = node.child("position"))
		loadPosition(widget, position);
	if (const auto& script = node.child("script"))
		loadScript(widget, script);
	if (const auto& size = node.child("size"))
		loadSize(widget, size);

	const std::string type = node.attribute("type").as_string();
	if (type == "panel")
		doLoad<LoaderPanel>(widget, node);
	else if (type == "button")
		doLoad<LoaderButton>(widget, node);
	else if (type == "checkbox")
		doLoad<LoaderButtonCheckbox>(widget, node);
	else if (type == "radio")
		doLoad<LoaderButtonRadio>(widget, node);
	else if (type == "label")
		doLoad<LoaderLabel>(widget, node);
	else if (type == "slider")
		doLoad<LoaderSlider>(widget, node);
	else if (type == "window")
		doLoad<LoaderWindow>(widget, node);
	else
		LOG(plog::warning) << "Unknown widget type " << type << " in gui " << m_path;

	if (const auto& clickable = node.child("clickable"))
		loadClickable(widget, clickable);
}
void hen::gui::Loader::loadAsset(Widget& widget, const pugi::xml_node& node) const
{
	for (auto& attribute = node.first_attribute(); attribute; attribute = attribute.next_attribute())
		widget.m_asset.addSprite(attribute.as_string(), attribute.name());
}
void hen::gui::Loader::loadBorder(Widget& widget, const pugi::xml_node& node) const
{
	float all = node.attribute("all").as_float();
	float inner = node.attribute("inner").as_float(all);
	float outer = node.attribute("outer").as_float(all);
	widget.m_border.setInner(
		node.attribute("inner_left").as_float(inner),
		node.attribute("inner_right").as_float(inner),
		node.attribute("inner_top").as_float(inner),
		node.attribute("inner_bottom").as_float(inner)
	);
	widget.m_border.setOuter(
		node.attribute("outer_left").as_float(outer),
		node.attribute("outer_right").as_float(outer),
		node.attribute("outer_top").as_float(outer),
		node.attribute("outer_bottom").as_float(outer)
	);
}
void hen::gui::Loader::loadClickable(Widget& widget, const pugi::xml_node& node) const
{
	widget.m_clickable.setLocked(node.attribute("locked").as_bool(false));

	if (node.attribute("active"))
		m_actives.push_back(&widget);
}
void hen::gui::Loader::loadFamily(Widget& widget, const pugi::xml_node& node) const
{
	static const std::string WIDGET_KEY = "widget";

	for (auto& child = node.first_child(); child; child = child.next_sibling())
	{
		if (WIDGET_KEY != child.name())
			continue;

		const std::string name = child.attribute("name").as_string();
		auto& childWidget = widget.getResources().createWidget(name, &widget);
		load(childWidget, child);
		loadFamily(childWidget, child);
	}
}
void hen::gui::Loader::loadGroup(Widget& widget, const pugi::xml_node& node) const
{
	if (const auto& leaderAttribute = node.attribute("leader"))
	{
		const std::string leaderName = leaderAttribute.as_string();
		auto& leader = widget.getResources().getWidget(leaderName);
		leader.m_group.add(&widget);
	}
}
void hen::gui::Loader::loadLink(Widget& widget, const pugi::xml_node& node) const
{
	const std::string targetName = node.attribute("target").as_string("PARENT");
	const std::string locationName = node.attribute("location").as_string(targetName == "PARENT" ? "top_left" : "right_top");

	const Widget* target = widget.m_family.getParent();
	const auto& resources = widget.getResources();
	if (resources.hasWidget(targetName) && targetName != "PARENT")
		target = &resources.getWidget(targetName);
	widget.m_link.setTarget(target);

	ComponentLink::Location location = ComponentLink::Location::LEFT_TOP;
	if (locationName == "top_left")
		location = ComponentLink::Location::TOP_LEFT;
	else if (locationName == "top")
		location = ComponentLink::Location::TOP;
	else if (locationName == "top_right")
		location = ComponentLink::Location::TOP_RIGHT;
	else if (locationName == "left_top")
		location = ComponentLink::Location::LEFT_TOP;
	else if (locationName == "right_top")
		location = ComponentLink::Location::RIGHT_TOP;
	else if (locationName == "left")
		location = ComponentLink::Location::LEFT;
	else if (locationName == "center")
		location = ComponentLink::Location::CENTER;
	else if (locationName == "right")
		location = ComponentLink::Location::RIGHT;
	else if (locationName == "left_bottom")
		location = ComponentLink::Location::LEFT_BOTTOM;
	else if (locationName == "right_bottom")
		location = ComponentLink::Location::RIGHT_BOTTOM;
	else if (locationName == "bottom_left")
		location = ComponentLink::Location::BOTTOM_LEFT;
	else if (locationName == "bottom")
		location = ComponentLink::Location::BOTTOM;
	else if (locationName == "bottom_right")
		location = ComponentLink::Location::BOTTOM_RIGHT;
	else
		LOG(plog::warning) << "Invalid link location " << locationName << " in gui " << m_path;
	widget.m_link.setLocation(location);

}
void hen::gui::Loader::loadPosition(Widget& widget, const pugi::xml_node& node) const
{
	const auto& offset = string::as_vec2(node.attribute("offset").as_string());
	widget.m_pos.setOffset(offset);
}
void hen::gui::Loader::loadScript(Widget& widget, const pugi::xml_node& node) const
{
	for (auto& attribute = node.first_attribute(); attribute; attribute = attribute.next_attribute())
		widget.m_script.set(attribute.name(), attribute.as_string());
}
void hen::gui::Loader::loadSize(Widget& widget, const pugi::xml_node& node) const
{
	if (const auto& attribute = node.attribute("size"))
		widget.m_size.setSize(string::as_vec2(attribute.as_string()));
	if (const auto& attribute = node.attribute("min"))
		widget.m_size.setMinSize(string::as_vec2(attribute.as_string()));
	if (const auto& attribute = node.attribute("max"))
		widget.m_size.setMaxSize(string::as_vec2(attribute.as_string()));
}


