
#include "hen/ui/gui/guis/GuiFile.h"

#include "hen/io/XMLFile.h"
#include "hen/logic/script/ScriptHelper.h"
#include "hen/ui/gui/loader/Loader.h"

void hen::gui::GuiFile::load(const std::string& filepath)
{
	if (getHandle() == nullptr)
		return;

	auto& resources = getHandle()->getResources();

	io::XMLFile xmlFile{ filepath };
	const auto& doc = xmlFile.open();
	const auto nodeLayout = doc.child("layout");
	const auto nodeScript = doc.child("script");

	script::ScriptHelper helper{ resources.getScript() };
	helper.addGlobalVariable(getHandle(), "Gui");
	if (nodeScript)
	{
		if (const auto attr = nodeScript.attribute("file"))
			helper.executeFile(attr.as_string());
		else
			helper.executeScript(nodeScript.child_value());
	}

	Loader loader{ *getHandle() };
	loader.load(nodeLayout, "");

	for (const auto& widget : resources.getWidgets())
	{
		if (widget->m_clickable.shouldBeInvokedAfterLoad())
			widget->m_clickable.invoke();
	}
}
