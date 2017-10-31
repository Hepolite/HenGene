
#include "hen/ui/gui/guis/Gui.h"

#include "hen/core/Core.h"
#include "hen/ui/gui/GuiManager.h"

#include "hen/io/XMLFile.h"
#include "hen/logic/script/ScriptHelper.h"
#include "hen/ui/gui/loader/Loader.h"


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

void hen::gui::Gui::load(const std::string& filepath)
{
	if (m_handle == nullptr)
		return;

	auto& resources = m_handle->getResources();

	io::XMLFile xmlFile{ filepath };
	const auto& doc = xmlFile.open();
	const auto nodeLayout = doc.child("layout");
	const auto nodeScript = doc.child("script");

	script::ScriptHelper helper{ resources.getScript() };
	helper.addGlobalVariable(m_handle, "Gui");
	if (nodeScript)
	{
		if (const auto attr = nodeScript.attribute("file"))
			helper.executeFile(attr.as_string());
		else
			helper.executeScript(nodeScript.child_value());
	}

	Loader loader{ *m_handle };
	loader.load(nodeLayout, "");

	for (const auto& widget : resources.getWidgets())
	{
		if (widget->m_clickable.shouldBeInvokedAfterLoad())
			widget->m_clickable.invoke();
	}
}

hen::script::Script& hen::gui::Gui::getScript()
{
	if (m_handle == nullptr)
		throw std::exception("Gui not opened");
	return m_handle->getResources().getScript();
}