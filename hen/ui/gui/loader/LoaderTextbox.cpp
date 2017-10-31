
#include "hen/ui/gui/loader/LoaderTextbox.h"

#include "hen/ui/gui/internal/Constants.h"
#include "hen/ui/gui/internal/GuiResources.h"
#include "hen/ui/gui/loader/LoaderButton.h"
#include "hen/ui/gui/loader/LoaderLabel.h"
#include "hen/ui/gui/loader/LoaderPanel.h"
#include "hen/ui/gui/processors/ProcessorTextbox.h"
#include "hen/util/MathLib.h"
#include "hen/util/StringLib.h"

void hen::gui::LoaderTextbox::load(const pugi::xml_node& node)
{
	const auto size = m_widget.m_size.getMinSize();

	LoaderPanel{ m_widget }.load(node);
	LoaderLabel{ m_widget }.load(node);

	ProcessorTextbox processor{ m_widget };
	m_widget.setRender(processor);

	restoreSize(size);
	limitTextSize();
}

void hen::gui::LoaderTextbox::restoreSize(const glm::vec2& size)
{
	m_widget.m_size.setMinSize(size);
}
void hen::gui::LoaderTextbox::limitTextSize()
{
	const auto& b = m_widget.m_border;
	const auto border = glm::vec2{ b.getInnerLeft() + b.getInnerRight(), b.getInnerTop() + b.getInnerBottom() };
	const auto size = m_widget.m_size.getMinSize() - border;

	auto text = m_widget.m_data.get<render::Text>(DATA_TEXT, render::Text{});
	text.setMaxWidth(math::min(size.x, text.getMaxWidth().value_or(size.x)));
	m_widget.m_data.set(DATA_TEXT, text);
}
