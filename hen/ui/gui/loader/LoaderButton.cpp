
#include "hen/ui/gui/loader/LoaderButton.h"

#include "hen/core/Core.h"
#include "hen/event/EventBus.h"
#include "hen/event/events/Mouse.h"
#include "hen/ui/gui/GuiResources.h"


void hen::gui::LoaderButton::render(const Widget& widget, const glm::vec2& offset, float dt)
{
	renderIcon(widget, offset);
}
void hen::gui::LoaderButton::renderIcon(const Widget& widget, const glm::vec2& offset)
{
	const auto& icon = widget.m_asset.getSprite("icon");
	if (icon == nullptr)
		return;
	const auto& clickable = widget.m_clickable;
	const auto& data = widget.m_data;

	const std::string state = clickable.isLocked() ? "locked" : clickable.isHovered() || clickable.isClicked() ? "hovered" : "normal";
	const std::string active = data.get<bool>("active") ? "active" : "inactive";
	unsigned int frame = icon->getFrameIndex(active + "_" + state);
	if (frame == -1)
		frame = icon->getFrameIndex(state);
	if (frame == -1)
		frame = 0;

	const auto& pos = widget.m_pos.getPos() + offset;
	const auto& size = widget.m_size.getSize();
	icon->render(frame, pos.x, pos.y, size.x, size.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void hen::gui::LoaderButton::load(Widget& widget, const pugi::xml_node& node) const
{
	widget.setRender(&LoaderButton::render);

	loadClickable(widget, node.child("clickable"));
	widget.m_data.set("inverted", node.child("clickable").attribute("inverted").as_bool());

	setupMouseEvent(widget);
}
void hen::gui::LoaderButton::loadClickable(Widget& widget, const pugi::xml_node& node) const
{
	widget.m_clickable.setInvoker([&]()
	{
		const bool inverted = widget.m_data.get<bool>("inverted");
		const auto& script = widget.m_script.get("click");
		if (!script.empty())
			widget.getResources().getScript().executeScript(script + "()");
	});
}

void hen::gui::LoaderButton::setupMouseEvent(Widget& widget) const
{
	auto& listener = widget.m_listener;

	listener.add(Core::getEventBus().registerCallback<events::MouseMove>([&](events::MouseMove& event)
	{
		const auto& bbox = (event.getScreenPos() - widget.m_pos.getPos()) / widget.m_size.getSize();
		widget.m_clickable.setHovered(widget.isVisible() && bbox.x >= 0.0f && bbox.x < 1.0f && bbox.y >= 0.0f && bbox.y < 1.0f);
	}));
	listener.add(Core::getEventBus().registerCallback<events::MousePress>([&](events::MousePress& event)
	{
		auto& clickable = widget.m_clickable;
		clickable.setClicked(widget.isVisible() && !clickable.isLocked() && clickable.isHovered());
	}));
	listener.add(Core::getEventBus().registerCallback<events::MouseRelease>([&](events::MouseRelease& event)
	{
		auto& clickable = widget.m_clickable;
		if (widget.isVisible() && !clickable.isLocked() && clickable.isClicked() && clickable.isHovered())
			clickable.invoke();
		clickable.setClicked(false);
	}));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void hen::gui::LoaderButtonCheckbox::load(Widget& widget, const pugi::xml_node& node) const
{
	LoaderButton loader;
	loader.load(widget, node);
	loadClickable(widget, node);
}
void hen::gui::LoaderButtonCheckbox::loadClickable(Widget& widget, const pugi::xml_node& node) const
{
	widget.m_clickable.setInvoker([&]()
	{
		bool active = !widget.m_data.get<bool>("active");
		widget.m_data.set("active", active);

		const bool inverted = widget.m_data.get<bool>("inverted");
		const auto& script = widget.m_script.get("click");
		if (!script.empty())
			widget.getResources().getScript().executeScript(script + (active != inverted ? "(true)" : "(false)"));
	});
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void hen::gui::LoaderButtonRadio::load(Widget& widget, const pugi::xml_node& node) const
{
	LoaderButton loader;
	loader.load(widget, node);
	loadClickable(widget, node);
}
void hen::gui::LoaderButtonRadio::loadClickable(Widget& widget, const pugi::xml_node& node) const
{
	widget.m_clickable.setInvoker([&]()
	{
		for (auto& member : widget.m_group.getMembers())
		{
			bool active = member->m_data.get<bool>("active");
			if (!active || member == &widget)
				continue;

			member->m_data.set("active", false);
			const bool inverted = member->m_data.get<bool>("inverted");
			const auto& script = member->m_script.get("click");
			if (!script.empty())
				widget.getResources().getScript().executeScript(script + (inverted ? "(true)" : "(false)"));
		}

		bool active = widget.m_data.get<bool>("active");
		if (!active)
		{
			widget.m_data.set("active", true);
			const bool inverted = widget.m_data.get<bool>("inverted");
			const auto& script = widget.m_script.get("click");
			if (!script.empty())
				widget.getResources().getScript().executeScript(script + (inverted ? "(false)" : "(true)"));
		}
	});
}
