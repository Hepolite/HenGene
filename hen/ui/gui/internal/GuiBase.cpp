
#include "hen/ui/gui/internal/GuiBase.h"

void hen::gui::GuiBase::process(float dt)
{
	if (m_resources.hasWidget())
		m_resources.getWidget().onProcess(dt);
}
void hen::gui::GuiBase::render(float dt) const
{
	if (m_resources.hasWidget())
		m_resources.getWidget().onRender(glm::vec2{}, dt);
}

