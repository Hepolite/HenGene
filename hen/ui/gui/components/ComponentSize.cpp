
#include "hen/ui/gui/components/ComponentSize.h"

#include "hen/ui/gui/Widget.h"
#include "hen/util/MathLib.h"

void hen::gui::ComponentSize::setMinSize(const glm::vec2& min)
{
	m_minSize = min;
	m_size = hen::math::max(m_minSize, m_size);
}

glm::vec2 hen::gui::ComponentSize::getMinSize(const Widget& widget, bool ignoreLimits) const
{
	const auto& border = widget.m_border;
	
	glm::vec2 minPosition;
	glm::vec2 minSize{ border.getInnerLeft() + border.getInnerRight(), border.getInnerTop() + border.getInnerBottom() };
	for (const auto& child : widget.m_family.getChildren())
	{
		if (!child->isVisible())
			continue;
		const auto pos = child->m_pos.getPos() - widget.m_pos.getPos();
		const auto size = child->m_size.getSize();
		minPosition = hen::math::min(minPosition, pos);
		minSize = hen::math::max(minSize, pos + size - minPosition);
	}
	const auto& finalSize = minSize + glm::vec2{ border.getInnerRight(), border.getInnerBottom() };
	if (ignoreLimits)
		return finalSize;
	return hen::math::min(m_maxSize, hen::math::max(m_minSize, finalSize));
}
