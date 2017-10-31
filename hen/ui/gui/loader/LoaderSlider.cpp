
#include "hen/ui/gui/loader/LoaderSlider.h"

#include "hen/ui/gui/loader/LoaderButton.h"
#include "hen/ui/gui/internal/Constants.h"
#include "hen/ui/gui/internal/GuiResources.h"
#include "hen/ui/gui/processors/ProcessorSlider.h"
#include "hen/util/MathLib.h"
#include "hen/util/StringLib.h"

void hen::gui::LoaderSlider::load(const pugi::xml_node& node)
{
	ProcessorSlider processor{ m_widget };
	m_widget.setInvoker(processor);
	m_widget.setProcess(processor);
	m_widget.setRender(processor);

	if (const auto childNode = node.child(COMPONENT_DATA))
		loadData(childNode);

	limitSize();
	createChildren();
}
void hen::gui::LoaderSlider::loadData(const pugi::xml_node& node)
{
	const auto attrLimit = string::as_vec2(node.attribute(ATTRIBUTE_DATA_LIMIT).as_string());
	const auto attrMiddle = node.attribute(ATTRIBUTE_DATA_MIDDLE).as_float();
	const auto attrSnap = node.attribute(ATTRIBUTE_DATA_SNAP).as_float();
	const auto attrValue = node.attribute(ATTRIBUTE_DATA_VALUE).as_float();

	m_widget.m_data.set(DATA_LIMIT, attrLimit);
	m_widget.m_data.set(DATA_MIDDLE, attrMiddle);
	m_widget.m_data.set(DATA_SNAP, attrSnap);
	m_widget.m_data.set(DATA_VALUE, attrValue);
}

void hen::gui::LoaderSlider::createChildren()
{
	auto& resources = m_widget.getResources();
	auto& buttonDecrease = resources.createWidget(m_widget.getName() + "_DECREASE", &m_widget);
	auto& buttonIncrease = resources.createWidget(m_widget.getName() + "_INCREASE", &m_widget);
	auto& buttonBar = resources.createWidget(m_widget.getName() + "_BAR", &m_widget);

	LoaderButton{ buttonDecrease }.load(pugi::xml_node{});
	LoaderButton{ buttonIncrease }.load(pugi::xml_node{});
	LoaderButton{ buttonBar }.load(pugi::xml_node{});

	ComponentLink::Location location;
	if (m_widget.m_size.getSize().x >= m_widget.m_size.getSize().y)
		location = ComponentLink::Location::RIGHT_TOP;
	else
		location = ComponentLink::Location::BOTTOM_LEFT;
	buttonDecrease.m_link.setTarget(&m_widget);
	buttonDecrease.m_link.setLocation(ComponentLink::Location::TOP_LEFT);
	buttonBar.m_link.setTarget(&buttonDecrease);
	buttonBar.m_link.setLocation(location);
	buttonIncrease.m_link.setTarget(&buttonBar);
	buttonIncrease.m_link.setLocation(location);

	loadChildButton(buttonDecrease, false);
	loadChildButton(buttonIncrease, true);
	loadChildBar(buttonBar);
}
void hen::gui::LoaderSlider::loadChildButton(Widget& child, bool incrementer) const
{
	const auto& size = m_widget.m_size.getMinSize();

	child.m_asset.addSprite(m_widget.m_asset.getPath(SPRITE_ICON), SPRITE_ICON);
	child.m_size.setMinSize(glm::vec2{ hen::math::min(size) });

	if (!incrementer)
		child.m_data.set<int>(DATA_RENDER_FLAGS, ALLEGRO_FLIP_HORIZONTAL);

	if (incrementer)
		child.setInvoker([&widget = m_widget]() { ProcessorSlider{ widget }.increment(); });
	else
		child.setInvoker([&widget = m_widget]() { ProcessorSlider{ widget }.decrement(); });
}
void hen::gui::LoaderSlider::loadChildBar(Widget& child) const
{
	const auto& size = m_widget.m_size.getMinSize();

	if (size.x >= size.y)
		child.m_size.setMinSize(glm::vec2{ size.x - 2.0f * size.y, size.y });
	else
		child.m_size.setMinSize(glm::vec2{ size.x, size.y - 2.0f * size.x });

	child.setRender(nullptr);
}

void hen::gui::LoaderSlider::limitSize()
{
	m_widget.m_size.setMaxSize(m_widget.m_size.getMinSize());
}
