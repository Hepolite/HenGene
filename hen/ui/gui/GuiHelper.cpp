
#include "hen/ui/gui/GuiHelper.h"

#include "hen/io/XMLFile.h"
#include "hen/logic/script/ScriptHelper.h"
#include "hen/ui/gui/loader/Loader.h"

void hen::gui::loadGuiFile(GuiBase& gui, const io::File& file)
{
	auto& resources = gui.getResources();

	io::XMLFile xmlFile{ file };
	const auto& doc = xmlFile.open();
	const auto nodeLayout = doc.child("layout");
	const auto nodeScript = doc.child("script");

	script::ScriptHelper helper{ resources.getScript() };
	helper.addGlobalVariable(&gui, "Gui");
	if (nodeScript)
	{
		if (const auto attr = nodeScript.attribute("file"))
			helper.executeFile(attr.as_string());
		else
			helper.executeScript(nodeScript.child_value());
	}

	Loader loader{ gui };
	loader.load(nodeLayout, "");

	for (const auto& widget : resources.getWidgets())
	{
		if (widget->m_clickable.shouldBeInvokedAfterLoad())
			widget->m_clickable.invoke();
	}
}

void hen::gui::loadMessageBox(GuiBase& gui, const std::string& message)
{
}
