
#include "hen/ui/gui/guis/Gui.h"

#include "hen/core/Core.h"
#include "hen/ui/gui/GuiManager.h"

void hen::gui::Gui::open(GuiLayer layer)
{
	close();
	m_handle = Core::getGuiManager().open(layer);
}
void hen::gui::Gui::close()
{
	Core::getGuiManager().close(m_handle);
	m_handle = nullptr;
}

hen::script::Script& hen::gui::Gui::getScript()
{
	if (m_handle == nullptr)
		throw std::exception("Gui not opened");
	return m_handle->getResources().getScript();
}
