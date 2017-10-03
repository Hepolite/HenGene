
#include "hen/ui/gui/Gui.h"

#include "hen/core/Core.h"
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
	script::ScriptHelper helper{ m_resources.getScript() };
	helper.addGlobalVariable(this, "Gui");

	Loader loader;
	loader.load(*this, file);
}
void hen::gui::Gui::onUnload()
{
	m_resources.clear();
}

hen::gui::Widget* hen::gui::Gui::getWidget(const std::string& name)
{
	return m_resources.hasWidget(name) ? &m_resources.getWidget(name) : nullptr;
}
