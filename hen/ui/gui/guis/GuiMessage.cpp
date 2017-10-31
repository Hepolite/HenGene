
#include "hen/ui/gui/guis/GuiMessage.h"

#include "hen/core/Core.h"
#include "hen/render/Text.h"
#include "hen/ui/gui/GuiManager.h"
#include "hen/ui/gui/internal/Constants.h"

void hen::gui::GuiMessage::open()
{
	Gui::open(GuiLayer::HIGH_PRIORITY);
	load("data/guis/core/message.xml");
	setCallback(nullptr);
}

void hen::gui::GuiMessage::setMessage(const std::string& message)
{
	if (getHandle() == nullptr || !getHandle()->hasWidget("box"))
		return;
	auto& widget = getHandle()->getWidget("box");

	auto text = widget.m_data.get<render::Text>(DATA_TEXT, render::Text{});
	text.setText(message);
	widget.m_data.set(DATA_TEXT, text);
}
void hen::gui::GuiMessage::setCallback(std::function<void()>&& callback)
{
	auto handle = getHandle();
	if (handle == nullptr || !handle->hasWidget("button"))
		return;
	auto& widget = handle->getWidget("button");

	widget.setInvoker([handle, invoker = std::move(callback)]()
	{
		if (invoker != nullptr)
			invoker();
		Core::getGuiManager().close(handle);
	});
}
