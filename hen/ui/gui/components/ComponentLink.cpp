
#include "hen/ui/gui/components/ComponentLink.h"

#include "hen/ui/gui/Widget.h"

glm::vec2 hen::gui::ComponentLink::getPos(const Widget& self) const
{
	if (m_target == nullptr)
		return glm::vec2{};
	const auto& pos = m_target->m_pos.getPos();
	if (m_target == self.m_family.getParent())
		return pos + getInner(self);
	else
		return pos + getOuter(self);
}
glm::vec2 hen::gui::ComponentLink::getInner(const Widget& self) const
{
	const auto& selfSize = self.m_size.getSize();
	const auto& targetSize = m_target->isVisible() ? m_target->m_size.getSize() : glm::vec2{};
	const auto& delta = targetSize - selfSize;
	const auto& border = m_target->isVisible() ? m_target->m_border : ComponentBorder{};

	switch (m_location)
	{
	case Location::TOP_LEFT:
	case Location::LEFT_TOP:
		return glm::vec2{ border.getInnerLeft(), border.getInnerTop() };
	case Location::TOP:
		return glm::vec2{ 0.5f * delta.x, border.getInnerTop() };
	case Location::TOP_RIGHT:
	case Location::RIGHT_TOP:
		return glm::vec2{ delta.x - border.getInnerRight(), border.getInnerTop() };
	case Location::LEFT:
		return glm::vec2{ border.getInnerLeft(), 0.5f * delta.y };
	case Location::CENTER:
		return 0.5f * delta;
	case Location::RIGHT:
		return glm::vec2{ delta.x - border.getInnerRight(), 0.5f * delta.y };
	case Location::LEFT_BOTTOM:
	case Location::BOTTOM_LEFT:
		return glm::vec2{ border.getInnerLeft(), delta.y - border.getInnerBottom() };
	case Location::BOTTOM:
		return glm::vec2{ 0.5f * delta.x, delta.y - border.getInnerBottom() };
	case Location::RIGHT_BOTTOM:
	case Location::BOTTOM_RIGHT:
		return glm::vec2{ delta.x - border.getInnerRight(), delta.y - border.getInnerBottom() };
	default:
		return glm::vec2{};
	}
}
glm::vec2 hen::gui::ComponentLink::getOuter(const Widget& self) const
{
	const auto& selfSize = self.m_size.getSize();
	const auto& targetSize = m_target->m_size.getSize();
	const auto& delta = targetSize - selfSize;
	const auto& border = m_target->m_border;

	switch (m_location)
	{
	case Location::TOP_LEFT:
		return glm::vec2{ 0.0f, -selfSize.y - border.getOuterTop() };
	case Location::TOP:
		return glm::vec2{ 0.5f * delta.x, -selfSize.y - border.getOuterTop() };
	case Location::TOP_RIGHT:
		return glm::vec2{ delta.x, -selfSize.y - border.getOuterTop() };
	case Location::LEFT_TOP:
		return glm::vec2{ -selfSize.x - border.getOuterLeft(), 0.0f };
	case Location::RIGHT_TOP:
		return glm::vec2{ targetSize.x + border.getOuterRight(), 0.0f };
	case Location::LEFT:
		return glm::vec2{ -selfSize.x - border.getOuterLeft(), 0.5f * delta.y };
	case Location::CENTER:
		return 0.5f * delta;
	case Location::RIGHT:
		return glm::vec2{ targetSize.x + border.getOuterRight(), 0.5f * delta.y };
	case Location::LEFT_BOTTOM:
		return glm::vec2{ -selfSize.x - border.getOuterLeft(), delta.y };
	case Location::RIGHT_BOTTOM:
		return glm::vec2{ targetSize.x + border.getOuterRight(), delta.y };
	case Location::BOTTOM_LEFT:
		return glm::vec2{ 0.0f, targetSize.y + border.getOuterBottom() };
	case Location::BOTTOM:
		return glm::vec2{ 0.5f * delta.x, targetSize.y + border.getOuterBottom() };
	case Location::BOTTOM_RIGHT:
		return glm::vec2{ delta.x, targetSize.y + border.getOuterBottom() };
	default:
		return glm::vec2{};
	}
}
