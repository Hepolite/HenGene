
#include "hen/ui/gui/loader/Loader.h"

#include "hen/core/Core.h"
#include "hen/ui/gui/internal/Constants.h"
#include "hen/ui/gui/internal/GuiBase.h"
#include "hen/ui/gui/internal/GuiResources.h"
#include "hen/ui/gui/loader/LoaderBase.h"
#include "hen/ui/gui/loader/LoaderButton.h"
#include "hen/ui/gui/loader/LoaderLabel.h"
#include "hen/ui/gui/loader/LoaderPanel.h"
#include "hen/ui/gui/loader/LoaderSlider.h"
#include "hen/ui/gui/loader/LoaderTextfield.h"
#include "hen/ui/gui/loader/LoaderWindow.h"
#include "hen/ui/Display.h"

#include <Log.h>

hen::gui::Loader::Loader(GuiBase& gui)
	: m_widget(gui.getResources().createWidget("", nullptr))
{
	const auto& display = hen::Core::getDisplay();
	m_widget.m_size.setMaxSize(glm::vec2{ display.getWidth(), display.getHeight() });
	m_widget.m_size.setMinSize(m_widget.m_size.getMaxSize());
}

void hen::gui::Loader::load(const pugi::xml_node& node, const std::string& type)
{
	LoaderBase{ m_widget }.load(node);

	if (type.empty())
		return;
	else if (type == TYPE_BUTTON)
		LoaderButton{ m_widget }.load(node);
	else if (type == TYPE_CHECKBOX)
		LoaderButtonCheckbox{ m_widget }.load( node);
	else if (type == TYPE_LABEL)
		LoaderLabel{ m_widget }.load(node);
	else if (type == TYPE_PANEL)
		LoaderPanel{ m_widget }.load(node);
	else if (type == TYPE_RADIO)
		LoaderButtonRadio{ m_widget }.load(node);
	else if (type == TYPE_TEXTFIELD)
		LoaderTextfield{}.load(m_widget, node);
	else if (type == TYPE_SLIDER)
		LoaderSlider{ m_widget }.load(node);
	else if (type == TYPE_WINDOW)
		LoaderWindow{}.load(m_widget, node);
	else
		LOG_WARNING << "Attempted to load unknown type " << type << " for widget " << m_widget.getName();
}

