
#include "hen/ui/gui/loader/LoaderPanel.h"

#include "hen/ui/gui/processors/ProcessorPanel.h"

void hen::gui::LoaderPanel::load(const pugi::xml_node& node) const
{
	ProcessorPanel processor{ m_widget };
	m_widget.setRender(processor);
}
