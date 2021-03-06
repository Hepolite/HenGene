
#include "hen/ui/gui/processors/ProcessorButton.h"

#include "hen/core/Core.h"
#include "hen/ui/gui/internal/Constants.h"
#include "hen/ui/gui/internal/GuiResources.h"
#include "hen/ui/Mouse.h"

namespace
{
	inline std::string getScriptArgument()
	{
		return "()";
	}
	inline std::string getScriptArgument(bool active, bool inverted)
	{
		return active != inverted ? "(true)" : "(false)";
	}
}

void hen::gui::ProcessorButton::operator()()
{
	const auto& script = m_widget.m_script.get(SCRIPT_CLICK);
	if (!script.empty())
		m_widget.getResources().getScript().executeScript(script + getScriptArgument());
}
void hen::gui::ProcessorButton::operator()(float dt)
{
	handleMouseMove();
	handleMousePress();
	handleMouseRelease();
}
void hen::gui::ProcessorButton::operator()(const glm::vec2& offset, float dt) const
{
	const auto& icon = m_widget.m_asset.getSprite(SPRITE_ICON);
	if (icon == nullptr)
		return;
	const auto& data = m_widget.m_data;

	auto frame = icon->getFrameIndex(getIconState());
	if (!frame)
		frame = icon->getFrameIndex(getIconClickState());

	const auto pos = m_widget.m_pos.getPos() + offset;
	const auto size = m_widget.m_size.getSize();
	const auto rotation = m_widget.m_data.get<float>(DATA_RENDER_ROTATION);
	const auto flags = data.get<int>(DATA_RENDER_FLAGS);
	icon->render(frame.value_or(0), pos.x, pos.y, size.x, size.y, rotation, flags);
}

void hen::gui::ProcessorButton::handleMouseMove()
{
	const auto bbox = (Core::getMouse().getPos() - m_widget.m_pos.getPos()) / m_widget.m_size.getSize();
	m_widget.m_clickable.setHovered(m_widget.isVisible() && bbox.x >= 0.0f && bbox.x < 1.0f && bbox.y >= 0.0f && bbox.y < 1.0f);
}
void hen::gui::ProcessorButton::handleMousePress()
{
	auto& clickable = m_widget.m_clickable;
	if ((m_widget.isVisible() && !clickable.isLocked() && clickable.isHovered()))
	{
		if (Core::getMouse().consumePressed(MOUSE_LEFT))
			clickable.setClicked(true);
	}
}
void hen::gui::ProcessorButton::handleMouseRelease()
{
	auto& clickable = m_widget.m_clickable;
	if (m_widget.isVisible() && !clickable.isLocked() && clickable.isHovered() && clickable.isClicked())
	{
		if (Core::getMouse().consumeReleased(MOUSE_LEFT))
		{
			clickable.invoke();
			clickable.setClicked(false);
		}
	}
}

std::string hen::gui::ProcessorButton::getIconState() const
{
	return getIconActiveState() + "_" + getIconClickState();
}
std::string hen::gui::ProcessorButton::getIconClickState() const
{
	const auto& clickable = m_widget.m_clickable;
	if (clickable.isLocked())
		return SPRITE_ICON_STATE_LOCKED;
	else if (clickable.isHovered() || clickable.isClicked())
		return SPRITE_ICON_STATE_HOVERED;
	else
		return SPRITE_ICON_STATE_NORMAL;
}
std::string hen::gui::ProcessorButton::getIconActiveState() const
{
	if (m_widget.m_data.get<bool>(DATA_ACTIVE))
		return SPRITE_ICON_STATE_ACTIVE;
	else
		return SPRITE_ICON_STATE_INACTIVE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void hen::gui::ProcessorButtonCheckbox::operator()()
{
	const bool active = m_widget.m_data.get<bool>(DATA_ACTIVE);
	const bool inverted = m_widget.m_data.get<bool>(DATA_INVERTED);
	const auto script = m_widget.m_script.get(SCRIPT_CLICK);

	if (!script.empty())
		m_widget.getResources().getScript().executeScript(script + getScriptArgument(!active, inverted));
	m_widget.m_data.set(DATA_ACTIVE, !active);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void hen::gui::ProcessorButtonRadio::operator()()
{
	for (auto& member : m_widget.m_group.getMembers())
	{
		const bool active = member->m_data.get<bool>(DATA_ACTIVE);
		if (!active || member == &m_widget)
			continue;
		const bool inverted = member->m_data.get<bool>(DATA_INVERTED);
		const auto script = member->m_script.get(SCRIPT_CLICK);

		if (!script.empty())
			member->getResources().getScript().executeScript(script + getScriptArgument(false, inverted));
		member->m_data.set(DATA_ACTIVE, false);
	}

	const bool active = m_widget.m_data.get<bool>(DATA_ACTIVE);
	const bool inverted = m_widget.m_data.get<bool>(DATA_INVERTED);
	const auto script = m_widget.m_script.get(SCRIPT_CLICK);

	if (!active && !script.empty())
		m_widget.getResources().getScript().executeScript(script + getScriptArgument(true, inverted));
	m_widget.m_data.set(DATA_ACTIVE, true);
}
