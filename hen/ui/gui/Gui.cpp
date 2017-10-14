
#include "hen/ui/gui/Gui.h"

#include "hen/core/Core.h"
#include "hen/io/XMLFile.h"
#include "hen/logic/script/ScriptHelper.h"
#include "hen/render/RenderCore.h"
#include "hen/ui/gui/loader/Loader.h"

hen::gui::Gui::Gui()
{
	m_renderer = Core::getRenderCore().addRenderer(render::RenderLayer::SCREEN, [this](float dt) { onRender(dt); });
}
hen::gui::Gui::~Gui()
{
	Core::getRenderCore().deleteRenderer(m_renderer);
}

void hen::gui::Gui::onProcess(float dt)
{
	if (m_resources.hasWidget())
		m_resources.getWidget().onProcess(dt);
}
void hen::gui::Gui::onRender(float dt) const
{
	if (m_resources.hasWidget())
		m_resources.getWidget().onRender(glm::vec2{}, dt);
}

void hen::gui::Gui::onLoad(const io::File& file)
{
	io::XMLFile xmlFile{ file };
	const auto& doc = xmlFile.open();
	const auto nodeLayout = doc.child("layout");
	const auto nodeScript = doc.child("script");

	script::ScriptHelper helper{ m_resources.getScript() };
	helper.addGlobalVariable(this, "Gui");
	if (nodeScript)
	{
		if (const auto attr = nodeScript.attribute("file"))
			helper.executeFile(attr.as_string());
		else
			helper.executeScript(nodeScript.child_value());
	}

	Loader loader{ *this };
	loader.load(nodeLayout, "");

	for (const auto& widget : m_resources.getWidgets())
	{
		if (widget->m_clickable.shouldBeInvokedAfterLoad())
			widget->m_clickable.invoke();
	}
}
void hen::gui::Gui::onUnload()
{
	m_resources.clear();
}

hen::gui::Widget* hen::gui::Gui::getWidget(const std::string& name)
{
	return m_resources.hasWidget(name) ? &m_resources.getWidget(name) : nullptr;
}
