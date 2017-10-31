
#include "hen/ui/gui/guis/GuiMessage.h"

void hen::gui::GuiMessage::open()
{
	Gui::open();
	load("data/guis/core/message.xml");
}

void hen::gui::GuiMessage::setMessage(const std::string& message)
{
}
void hen::gui::GuiMessage::setCallback(std::function<void()>&& callback)
{
}
