
#include "hen/ui/gui/processors/ProcessorPanel.h"

#include "hen/ui/gui/internal/Constants.h"
#include "hen/util/MathLib.h"

void hen::gui::ProcessorPanel::operator()(const glm::vec2& offset, float dt) const
{
	renderBackground(offset, dt);
	renderChildren(offset, dt);
}

void hen::gui::ProcessorPanel::renderBackground(const glm::vec2& offset, float dt) const
{
	const auto& background = m_widget.m_asset.getSprite(SPRITE_BACKGROUND);
	if (background == nullptr)
		return;
	const auto cornerFrame = background->getFrame(0);
	const auto centerFrame = background->getFrame(4);
	if (!cornerFrame || !centerFrame)
		return;

	const auto size = m_widget.m_size.getSize();
	const auto sizeCorner = hen::math::min(glm::vec2{ cornerFrame->m_w, cornerFrame->m_h }, 0.5f * size);
	const auto sizeCenter = size - 2.0f * sizeCorner;
	const auto pos = m_widget.m_pos.getPos() + offset;
	const auto posCenter = pos + sizeCorner;
	const auto posCorner = posCenter + sizeCenter;

	background->render(0, pos.x, pos.y, sizeCorner.x, sizeCorner.y);
	background->render(1, posCenter.x, pos.y, sizeCenter.x, sizeCorner.y);
	background->render(2, posCorner.x, pos.y, sizeCorner.x, sizeCorner.y);
	background->render(3, pos.x, posCenter.y, sizeCorner.x, sizeCenter.y);
	background->render(4, posCenter.x, posCenter.y, sizeCenter.x, sizeCenter.y);
	background->render(5, posCorner.x, posCenter.y, sizeCorner.x, sizeCenter.y);
	background->render(6, pos.x, posCorner.y, sizeCorner.x, sizeCorner.y);
	background->render(7, posCenter.x, posCorner.y, sizeCenter.x, sizeCorner.y);
	background->render(8, posCorner.x, posCorner.y, sizeCorner.x, sizeCorner.y);
}
void hen::gui::ProcessorPanel::renderChildren(const glm::vec2& offset, float dt) const
{
	for (auto& child : m_widget.m_family.getChildren())
		child->onRender(offset, dt);
}
