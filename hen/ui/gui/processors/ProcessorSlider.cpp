
#include "hen/ui/gui/processors/ProcessorSlider.h"

#include "hen/core/Core.h"
#include "hen/ui/gui/internal/Constants.h"
#include "hen/ui/gui/internal/GuiResources.h"
#include "hen/ui/Mouse.h"
#include "hen/util/MathLib.h"

namespace
{
	inline std::string getScriptArgument(float value)
	{
		return "(" + std::to_string(value) + ")";
	}
}

void hen::gui::ProcessorSlider::operator()()
{
	const auto& script = m_widget.m_script.get(SCRIPT_CHANGE);
	const auto& value = m_widget.m_data.get<float>(DATA_VALUE);
	if (!script.empty())
		m_widget.getResources().getScript().executeScript(script + getScriptArgument(value));
}
void hen::gui::ProcessorSlider::operator()(float dt)
{
	processChildren(dt);
	processSlider(dt);
}
void hen::gui::ProcessorSlider::operator()(const glm::vec2& offset, float dt) const
{
	renderBar(offset, dt);
	renderSlider(offset, dt);
}

void hen::gui::ProcessorSlider::processChildren(float dt)
{
	const auto locked = m_widget.m_clickable.isLocked();

	for (auto& child : m_widget.m_family.getChildren())
		child->m_clickable.setLocked(locked);
}
void hen::gui::ProcessorSlider::processSlider(float dt)
{
	const auto& bar = m_widget.m_family.getChildren()[2];
	if (!bar->m_clickable.isClicked())
		return;

	const auto size = m_widget.m_size.getSize();
	const auto index = size.x >= size.y ? 0 : 1;
	const auto mousePos = hen::Core::getMouse().getPos()[index];
	const auto ratio = (mousePos - bar->m_pos.getPos()[index]) / bar->m_size.getSize()[index];

	const auto middle = m_widget.m_data.get<float>(DATA_MIDDLE);
	const auto limit = m_widget.m_data.get<glm::vec2>(DATA_LIMIT);
	if (ratio < 0.5f)
		setValue(hen::math::lerp(limit.x, middle, 2.0f * ratio));
	else
		setValue(hen::math::lerp(middle, limit.y, 2.0f * ratio - 1.0f));
}

void hen::gui::ProcessorSlider::renderBar(const glm::vec2& offset, float dt) const
{
	const auto& bar = m_widget.m_asset.getSprite("bar");
	if (bar == nullptr)
		return;
	const auto button = m_widget.m_family.getChildren()[2];
	const auto& clickable = button->m_clickable;
	const auto& data = button->m_data;

	const auto frame = bar->getFrameIndex(getIconClickState(*button)).value_or(0);
	const auto cornerFrame = bar->getFrame(frame + 0);
	const auto centerFrame = bar->getFrame(frame + 1);
	if (!cornerFrame || !centerFrame)
		return;

	const auto size = button->m_size.getSize();
	const auto sizeCorner = hen::math::min(glm::vec2{ cornerFrame->m_w, cornerFrame->m_h }, 0.5f * size);
	const auto sizeCenter = size - 2.0f * sizeCorner;
	const auto pos = button->m_pos.getPos() + offset;
	const auto posCenter = pos + sizeCorner;
	const auto posCorner = posCenter + sizeCenter;

	if (size.x >= size.y)
	{
		bar->render(frame + 0, pos.x, pos.y, sizeCorner.x, size.y);
		bar->render(frame + 1, posCenter.x, pos.y, sizeCenter.x, size.y);
		bar->render(frame + 2, posCorner.x, pos.y, sizeCorner.x, size.y);
	}
	else
	{
		bar->render(frame + 0, pos.x, pos.y, size.x, sizeCorner.y);
		bar->render(frame + 1, pos.x, posCenter.y, size.x, sizeCenter.y);
		bar->render(frame + 2, pos.x, posCorner.y, size.x, sizeCorner.y);
	}
}
void hen::gui::ProcessorSlider::renderSlider(const glm::vec2& offset, float dt) const
{
	const auto& slider = m_widget.m_asset.getSprite(SPRITE_SLIDER);
	if (slider == nullptr)
		return;
	const auto& button = m_widget.m_family.getChildren()[2];
	const auto& clickable = button->m_clickable;

	unsigned int frame = slider->getFrameIndex(getIconClickState(m_widget)).value_or(0);
	const auto value = m_widget.m_data.get<float>(DATA_VALUE);
	const auto middle = m_widget.m_data.get<float>(DATA_MIDDLE);
	const auto limit = m_widget.m_data.get<glm::vec2>(DATA_LIMIT);
	const auto ratio = 0.5f * (value < middle ? (value - limit.x) / (middle - limit.x) : 2.0f - (limit.y - value) / (limit.y - middle));

	const auto& size = button->m_size.getSize() - slider->getFrame(frame).value_or(allegro::Sprite::Frame{}).m_w;
	const auto& pos = button->m_pos.getPos() + offset;
	slider->render(frame, pos.x + ratio * size.x, pos.y);
}

float hen::gui::ProcessorSlider::getSnap() const
{
	return m_widget.m_data.get<float>(DATA_SNAP);
}
float hen::gui::ProcessorSlider::getValue() const
{
	return m_widget.m_data.get<float>(DATA_VALUE);
}
void hen::gui::ProcessorSlider::setValue(float value)
{
	const auto limit = m_widget.m_data.get<glm::vec2>(DATA_LIMIT);
	const auto snap = m_widget.m_data.get<float>(DATA_SNAP);

	const auto snappedValue = snap == 0.0f ? value : hen::math::round(value / snap) * snap;
	const auto limitedValue = hen::math::max(limit.x, hen::math::min(limit.y, snappedValue));
	if (limitedValue != getValue())
	{
		m_widget.m_data.set(DATA_VALUE, limitedValue);
		m_widget.click();
	}
}
void hen::gui::ProcessorSlider::increment()
{
	setValue(getValue() + getSnap());
}
void hen::gui::ProcessorSlider::decrement()
{
	setValue(getValue() - getSnap());
}

std::string hen::gui::ProcessorSlider::getIconClickState(Widget& widget) const
{
	const auto& clickable = widget.m_clickable;
	if (clickable.isLocked())
		return SPRITE_ICON_STATE_LOCKED;
	else if (clickable.isHovered() || clickable.isClicked())
		return SPRITE_ICON_STATE_HOVERED;
	else
		return SPRITE_ICON_STATE_NORMAL;
}
