
#include "hen/ui/gui/loader/LoaderWindow.h"

#include "hen/ui/gui/GuiResources.h"
#include "hen/ui/gui/loader/LoaderSlider.h"
#include "hen/util/MathLib.h"

#include <allegro5/display.h>
#include <allegro5/drawing.h>

void hen::gui::LoaderWindow::process(Widget& widget, float dt)
{
	auto& resources = widget.getResources();
	auto& horizontal = resources.getWidget(widget.getName() + "_HORIZONTAL");
	auto& vertical = resources.getWidget(widget.getName() + "_VERTICAL");

	const auto& size = hen::math::max(glm::vec2{}, widget.m_size.getMinSize(widget, true) - widget.m_size.getSize());
	horizontal.m_clickable.setLocked(size.x == 0.0f);
	vertical.m_clickable.setLocked(size.y == 0.0f);
	LoaderSlider::setLimit(horizontal, glm::vec2{ 0, size.x }, 0.5f * size.x);
	LoaderSlider::setLimit(vertical, glm::vec2{ 0, size.y }, 0.5f * size.y);
}
void hen::gui::LoaderWindow::render(const Widget& widget, const glm::vec2& offset, float dt)
{
	const auto& target = widget.m_asset.getSprite("window");
	if (target == nullptr)
		return;

	auto& resources = widget.getResources();
	auto& horizontal = resources.getWidget(widget.getName() + "_HORIZONTAL");
	auto& vertical = resources.getWidget(widget.getName() + "_VERTICAL");
	const glm::vec2 displacement{ LoaderSlider::getValue(horizontal), LoaderSlider::getValue(vertical) };

	ALLEGRO_BITMAP* backbuffer = al_get_target_bitmap();
	al_set_target_bitmap(target->getHandle());
	al_clear_to_color(ALLEGRO_COLOR{ 0.0f, 0.0, 0.0f, 0.0f });
	const auto& children = widget.m_family.getChildren();
	for (unsigned int i = 2; i < children.size(); ++i)
		children[i]->onRender(offset - widget.m_pos.getPos() - displacement, dt);
	al_set_target_bitmap(backbuffer);

	const auto& pos = widget.m_pos.getPos() + offset;
	target->render(pos.x, pos.y);
	children[0]->onRender(offset, dt);
	children[1]->onRender(offset, dt);
}

//////////////////////////////////////////////////////////////////////////

void hen::gui::LoaderWindow::load(Widget& widget, const pugi::xml_node& node) const
{
	const auto& size = glm::ivec2{ widget.m_size.getSize() };
	widget.m_asset.createSprite(size.x, size.y, "window");

	widget.setProcess(&LoaderWindow::process);
	widget.setRender(&LoaderWindow::render);

	loadSliders(widget);
}
void hen::gui::LoaderWindow::loadSliders(Widget& widget) const
{
	auto& resources = widget.getResources();
	auto& horizontal = resources.createWidget(widget.getName() + "_HORIZONTAL", &widget);
	auto& vertical = resources.createWidget(widget.getName() + "_VERTICAL", &widget);

	loadSlider(widget, horizontal, false);
	loadSlider(widget, vertical, true);

	horizontal.m_link.setTarget(&widget);
	horizontal.m_link.setLocation(ComponentLink::Location::BOTTOM_LEFT);
	vertical.m_link.setTarget(&widget);
	vertical.m_link.setLocation(ComponentLink::Location::TOP_RIGHT);
}
void hen::gui::LoaderWindow::loadSlider(Widget& widget, Widget& slider, bool vertical) const
{
	const auto& size = widget.m_size.getMinSize();
	if (vertical)
		slider.m_size.setMinSize(glm::vec2{ 16.0f, size.y - 16.0f });
	else
		slider.m_size.setMinSize(glm::vec2{ size.x - 16.0f, 16.0f });

	slider.m_asset.addSprite(widget.m_asset.getPath("bar"), "bar");
	slider.m_asset.addSprite(widget.m_asset.getPath("icon"), "icon");
	slider.m_asset.addSprite(widget.m_asset.getPath("slider"), "slider");

	LoaderSlider loader;
	loader.load(slider, pugi::xml_node{});
}
