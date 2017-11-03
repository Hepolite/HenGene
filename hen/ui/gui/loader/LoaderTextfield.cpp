
#include "hen/ui/gui/loader/LoaderTextfield.h"

#include "hen/ui/gui/loader/LoaderTextbox.h"
#include "hen/ui/gui/processors/ProcessorTextfield.h"

void hen::gui::LoaderTextfield::load(const pugi::xml_node& node)
{
	LoaderTextbox{ m_widget }.load(node);

	ProcessorTextfield processor{ m_widget };
	m_widget.setProcess(processor);
}
