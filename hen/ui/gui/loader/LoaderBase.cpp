
#include "hen/ui/gui/loader/LoaderBase.h"

#include "hen/ui/gui/internal/Constants.h"
#include "hen/ui/gui/internal/GuiResources.h"
#include "hen/ui/gui/loader/Loader.h"
#include "hen/util/StringLib.h"

#include <Log.h>

void hen::gui::LoaderBase::load(const pugi::xml_node& node)
{
	loadHeader(node);
	loadFamily(node);

	if (const auto& childNode = node.child(COMPONENT_BORDER))
		loadBorder(childNode);
	if (const auto& childNode = node.child(COMPONENT_CLICKABLE))
		loadClickable(childNode);
	if (const auto& childNode = node.child(COMPONENT_POSITION))
		loadPosition(childNode);
	if (const auto& childNode = node.child(COMPONENT_SCRIPT))
		loadScript(childNode);
	if (const auto& childNode = node.child(COMPONENT_SIZE))
		loadSize(childNode);
	if (const auto& childNode = node.child(COMPONENT_SPRITE))
		loadSprite(childNode);

	assignDefaultGroup();
	if (const auto& childNode = node.child(COMPONENT_GROUP))
		loadGroup(childNode);
	if (const auto& childNode = node.child(COMPONENT_LINK))
		loadLink(childNode);
	else
		assignDefaultLink();
}

void hen::gui::LoaderBase::loadHeader(const pugi::xml_node& node)
{
	const auto attrVisible = node.attribute(ATTRIBUTE_HEADER_VISIBLE).as_bool(true);

	m_widget.setVisible(attrVisible);
}
void hen::gui::LoaderBase::loadFamily(const pugi::xml_node& node)
{
	for (auto& component = node.child(COMPONENT_WIDGET); component; component = component.next_sibling())
	{
		const std::string attrName = component.attribute(ATTRIBUTE_WIDGET_NAME).as_string();
		const std::string attrType = component.attribute(ATTRIBUTE_WIDGET_TYPE).as_string();

		auto& child = m_widget.getResources().createWidget(attrName, &m_widget);
		Loader loader{ child };
		loader.load(component, attrType);
	}
}
void hen::gui::LoaderBase::loadBorder(const pugi::xml_node& node)
{
	const auto attrAll = node.attribute(ATTRIBUTE_BORDER_ALL).as_float();
	const auto attrInner = node.attribute(ATTRIBUTE_BORDER_INNER).as_float(attrAll);
	const auto attrInnerBottom = node.attribute(ATTRIBUTE_BORDER_INNER_BOTTOM).as_float(attrInner);
	const auto attrInnerLeft = node.attribute(ATTRIBUTE_BORDER_INNER_LEFT).as_float(attrInner);
	const auto attrInnerRight = node.attribute(ATTRIBUTE_BORDER_INNER_RIGHT).as_float(attrInner);
	const auto attrInnerTop = node.attribute(ATTRIBUTE_BORDER_INNER_TOP).as_float(attrInner);
	const auto attrOuter = node.attribute(ATTRIBUTE_BORDER_OUTER).as_float(attrAll);
	const auto attrOuterBottom = node.attribute(ATTRIBUTE_BORDER_OUTER_BOTTOM).as_float(attrOuter);
	const auto attrOuterLeft = node.attribute(ATTRIBUTE_BORDER_OUTER_LEFT).as_float(attrOuter);
	const auto attrOuterRight = node.attribute(ATTRIBUTE_BORDER_OUTER_RIGHT).as_float(attrOuter);
	const auto attrOuterTop = node.attribute(ATTRIBUTE_BORDER_OUTER_TOP).as_float(attrOuter);

	m_widget.m_border.setInner(attrInnerLeft, attrInnerRight, attrInnerTop, attrInnerBottom);
	m_widget.m_border.setOuter(attrOuterLeft, attrOuterRight, attrOuterTop, attrOuterBottom);
}
void hen::gui::LoaderBase::loadClickable(const pugi::xml_node& node)
{
	const auto attrActive = node.attribute(ATTRIBUTE_CLICKABLE_ACTIVE).as_bool();
	const auto attrLocked = node.attribute(ATTRIBUTE_CLICKABLE_LOCKED).as_bool();

	m_widget.m_clickable.setLocked(attrLocked);
	if (attrActive)
		m_widget.m_clickable.markForInvokationAfterLoad();
}
void hen::gui::LoaderBase::loadGroup(const pugi::xml_node& node)
{
	const std::string attrLeader = node.attribute(ATTRIBUTE_GROUP_LEADER).as_string();

	auto& resources = m_widget.getResources();
	if (!attrLeader.empty() && resources.hasWidget(attrLeader))
		resources.getWidget(attrLeader).m_group.add(&m_widget);
}
void hen::gui::LoaderBase::loadLink(const pugi::xml_node& node)
{
	const std::string attrTarget = node.attribute(ATTRIBUTE_LINK_TARGET).as_string(LINK_PARENT.c_str());
	const std::string attrLocation = node.attribute(ATTRIBUTE_LINK_LOCATION).as_string(
		(attrTarget == LINK_PARENT ? LINK_TOP_LEFT : LINK_RIGHT_TOP).c_str()
	);

	const auto& resources = m_widget.getResources();
	if (attrTarget == LINK_PARENT)
		m_widget.m_link.setTarget(m_widget.m_family.getParent());
	else if (resources.hasWidget(attrTarget))
		m_widget.m_link.setTarget(&resources.getWidget(attrTarget));

	ComponentLink::Location location = ComponentLink::Location::LEFT_TOP;
	if (attrLocation == LINK_TOP_LEFT)
		location = ComponentLink::Location::TOP_LEFT;
	else if (attrLocation == LINK_TOP)
		location = ComponentLink::Location::TOP;
	else if (attrLocation == LINK_TOP_RIGHT)
		location = ComponentLink::Location::TOP_RIGHT;
	else if (attrLocation == LINK_LEFT)
		location = ComponentLink::Location::LEFT_TOP;
	else if (attrLocation == LINK_RIGHT_TOP)
		location = ComponentLink::Location::RIGHT_TOP;
	else if (attrLocation == LINK_LEFT)
		location = ComponentLink::Location::LEFT;
	else if (attrLocation == LINK_CENTER)
		location = ComponentLink::Location::CENTER;
	else if (attrLocation == LINK_RIGHT)
		location = ComponentLink::Location::RIGHT;
	else if (attrLocation == LINK_LEFT_BOTTOM)
		location = ComponentLink::Location::LEFT_BOTTOM;
	else if (attrLocation == LINK_RIGHT_BOTTOM)
		location = ComponentLink::Location::RIGHT_BOTTOM;
	else if (attrLocation == LINK_BOTTOM_LEFT)
		location = ComponentLink::Location::BOTTOM_LEFT;
	else if (attrLocation == LINK_BOTTOM)
		location = ComponentLink::Location::BOTTOM;
	else if (attrLocation == LINK_BOTTOM_RIGHT)
		location = ComponentLink::Location::BOTTOM_RIGHT;
	else
		LOG_WARNING << "Invalid link location " << attrLocation << " in widget " << m_widget.getName();
	m_widget.m_link.setLocation(location);
}
void hen::gui::LoaderBase::loadPosition(const pugi::xml_node& node)
{
	const auto attrOffset = string::as_vec2(node.attribute(ATTRIBUTE_POSITION_OFFSET).as_string());

	m_widget.m_pos.setOffset(attrOffset);
}
void hen::gui::LoaderBase::loadScript(const pugi::xml_node& node)
{
	for (auto& attr = node.first_attribute(); attr; attr = attr.next_attribute())
		m_widget.m_script.set(attr.name(), attr.as_string());
}
void hen::gui::LoaderBase::loadSize(const pugi::xml_node& node)
{
	if (const auto& attr = node.attribute(ATTRIBUTE_SIZE_SIZE))
		m_widget.m_size.setSize(string::as_vec2(attr.as_string()));
	if (const auto& attr = node.attribute(ATTRIBUTE_SIZE_MIN))
		m_widget.m_size.setMinSize(string::as_vec2(attr.as_string()));
	if (const auto& attr = node.attribute(ATTRIBUTE_SIZE_MAX))
		m_widget.m_size.setMaxSize(string::as_vec2(attr.as_string()));
}
void hen::gui::LoaderBase::loadSprite(const pugi::xml_node& node)
{
	for (auto& attr = node.first_attribute(); attr; attr = attr.next_attribute())
		m_widget.m_asset.addSprite(attr.as_string(), attr.name());
}

void hen::gui::LoaderBase::assignDefaultGroup()
{
	m_widget.m_group.add(&m_widget);
}
void hen::gui::LoaderBase::assignDefaultLink()
{
	m_widget.m_link.setTarget(m_widget.m_family.getParent());
}
