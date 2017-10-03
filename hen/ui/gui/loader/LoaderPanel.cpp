
#include "hen/ui/gui/loader/LoaderPanel.h"

#include "hen/ui/gui/GuiResources.h"
#include "hen/util/MathLib.h"

void hen::gui::LoaderPanel::load(Widget& widget, const pugi::xml_node& node) const
{
	widget.setRender(&LoaderPanel::render);
}

void hen::gui::LoaderPanel::render(const Widget& widget, const glm::vec2& offset, float dt)
{
	renderBackground(widget, offset);
	for (auto& child : widget.m_family.getChildren())
		child->onRender(offset, dt);
}
void hen::gui::LoaderPanel::renderBackground(const Widget& widget, const glm::vec2& offset)
{
	const auto& background = widget.m_asset.getSprite("background");
	if (background == nullptr)
		return;

	const auto cornerFrame = background->getFrame(0);
	const auto centerFrame = background->getFrame(4);
	const auto& size = widget.m_size.getSize();
	const auto& sizeCorner = hen::math::min(glm::vec2{ cornerFrame.m_w, cornerFrame.m_h }, 0.5f * size);
	const auto& sizeCenter = size - 2.0f * sizeCorner;
	const auto& pos = widget.m_pos.getPos() + offset;
	const auto& posCenter = pos + sizeCorner;
	const auto& posCorner = posCenter + sizeCenter;

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
