
#include "hen/ui/gui/loader/LoaderButton.h"

#include "hen/core/Core.h"
#include "hen/event/EventBus.h"
#include "hen/event/events/Mouse.h"
#include "hen/ui/gui/Constants.h"
#include "hen/ui/gui/processors/ProcessorButton.h"

void hen::gui::LoaderButton::load(const pugi::xml_node& node)
{
	ProcessorButton processor{ m_widget };
	m_widget.setInvoker(processor);
	m_widget.setRender(processor);

	m_widget.m_listener.add(Core::getEventBus().registerCallback<events::MouseMove>(processor));
	m_widget.m_listener.add(Core::getEventBus().registerCallback<events::MousePress>(processor));
	m_widget.m_listener.add(Core::getEventBus().registerCallback<events::MouseRelease>(processor));

	if (const auto childNode = node.child(COMPONENT_CLICKABLE))
		loadClickable(childNode);
}
void hen::gui::LoaderButton::loadClickable(const pugi::xml_node& node)
{
	const auto attrInverted = node.attribute(ATTRIBUTE_CLICKABLE_INVERTED).as_bool();

	m_widget.m_data.set(DATA_INVERTED, attrInverted);
}

void hen::gui::LoaderButtonCheckbox::load(const pugi::xml_node& node)
{
	LoaderButton{ m_widget }.load(node);
	
	ProcessorButtonCheckbox processor{ m_widget };
	m_widget.setInvoker(processor);
}

void hen::gui::LoaderButtonRadio::load(const pugi::xml_node& node)
{
	LoaderButton{ m_widget }.load(node);
	
	ProcessorButtonRadio processor{ m_widget };
	m_widget.setInvoker(processor);
}
