
#include "hen/ui/gui/GuiResources.h"

#include <Log.h>

hen::gui::Widget& hen::gui::GuiResources::createWidget(const std::string& name, Widget* parent)
{
	const auto& result = m_widgets.find(name);
	if (result != m_widgets.end())
		throw std::invalid_argument("Widget " + name + " already exists!");
	
	const auto& insert = m_widgets.emplace(
		std::piecewise_construct,
		std::make_tuple(name),
		std::make_tuple(name, parent)
	);
	insert.first->second.m_data.set<GuiResources*>("", this);
	return insert.first->second;
}
hen::gui::Widget& hen::gui::GuiResources::getWidget(const std::string& name)
{
	const auto& result = m_widgets.find(name);
	if (result == m_widgets.end())
		throw std::invalid_argument("Widget " + name + " does not exist!");
	return result->second;
}
bool hen::gui::GuiResources::hasWidget(const std::string& name) const
{
	return m_widgets.find(name) != m_widgets.end();
}
const hen::gui::Widget& hen::gui::GuiResources::getWidget(const std::string& name) const
{
	const auto& result = m_widgets.find(name);
	if (result == m_widgets.end())
		throw std::invalid_argument("Widget " + name + " does not exist!");
	return result->second;
}
std::vector<hen::gui::Widget*> hen::gui::GuiResources::getWidgets()
{
	std::vector<Widget*> widgets;
	for (auto& it : m_widgets)
		widgets.emplace_back(&it.second);
	return widgets;
}
