
#include "hen/ui/gui/loader/LoaderSlider.h"

#include "hen/ui/gui/loader/LoaderButton.h"

#include "hen/core/Core.h"
#include "hen/ui/gui/GuiResources.h"
#include "hen/ui/Mouse.h"
#include "hen/util/MathLib.h"
#include "hen/util/StringLib.h"

namespace
{
	const unsigned int BUTTON_DECREASE = 0;
	const unsigned int BUTTON_INCREASE = 1;
	const unsigned int BUTTON_BAR = 2;

	const char* DATA_MIDDLE = "middle";
	const char* DATA_LIMIT = "limit";
	const char* DATA_SNAP = "snap";
	const char* DATA_VALUE = "value";

	const std::string SCRIPT_CHANGE = "change";
	const std::string SPRITE_ICON = "icon";
	const std::string SPRITE_SLIDER = "slider";
}

void hen::gui::LoaderSlider::process(Widget& widget, float dt)
{
	auto& children = widget.m_family.getChildren();
	for (auto& child : children)
		child->m_clickable.setLocked(widget.m_clickable.isLocked());

	const auto& bar = children[BUTTON_BAR];
	if (bar->m_clickable.isClicked())
	{
		const auto size = widget.m_size.getSize();
		const auto index = size.x >= size.y ? 0 : 1;
		const auto mousePos = hen::Core::getMouse().getPos()[index];
		const auto ratio = (mousePos - bar->m_pos.getPos()[index]) / bar->m_size.getSize()[index];

		const auto middle = widget.m_data.get<float>(DATA_MIDDLE);
		const auto limit = widget.m_data.get<glm::vec2>(DATA_LIMIT);
		if (ratio < 0.5f)
			setValue(widget, hen::math::lerp(limit.x, middle, 2.0f * ratio));
		else
			setValue(widget, hen::math::lerp(middle, limit.y, 2.0f * ratio - 1.0f));
	}
}
void hen::gui::LoaderSlider::render(const Widget& widget, const glm::vec2& offset, float dt)
{
	renderBar(widget, offset);
	renderSlider(widget, offset);

	for (const auto& child : widget.m_family.getChildren())
		child->onRender(offset, dt);
}
void hen::gui::LoaderSlider::renderBar(const Widget& widget, const glm::vec2& offset)
{
	const auto& bar = widget.m_asset.getSprite("bar");
	if (bar == nullptr)
		return;
	const auto& button = widget.m_family.getChildren()[BUTTON_BAR];
	const auto& clickable = button->m_clickable;
	const auto& data = button->m_data;

	const std::string state = clickable.isLocked() ? "locked" : clickable.isHovered() || clickable.isClicked() ? "hovered" : "normal";
	unsigned int frame = bar->getFrameIndex(state);
	if (frame == -1)
		frame = 0;

	const auto& cornerFrame = bar->getFrame(frame + 0);
	const auto& centerFrame = bar->getFrame(frame + 1);
	const auto& size = button->m_size.getSize();
	const auto& sizeCorner = hen::math::min(glm::vec2{ cornerFrame.m_w, cornerFrame.m_h }, 0.5f * size);
	const auto& sizeCenter = size - 2.0f * sizeCorner;
	const auto& pos = button->m_pos.getPos() + offset;
	const auto& posCenter = pos + sizeCorner;
	const auto& posCorner = posCenter + sizeCenter;

	if (size.x >= size.y)
	{
		bar->render(frame + 0, pos.x, pos.y, sizeCorner.x, size.y);
		bar->render(frame + 1, posCenter.x, pos.y, sizeCenter.x, size.y);
		bar->render(frame + 2, posCorner.x, pos.y, sizeCorner.x, size.y);
	}
	else
	{
		bar->render(frame + 0, pos.x, pos.y, size.x, sizeCorner.y);
		bar->render(frame + 1, pos.x, posCenter.y, size.x, sizeCenter.y);
		bar->render(frame + 2, pos.x, posCorner.y, size.x, sizeCorner.y);
	}
}
void hen::gui::LoaderSlider::renderSlider(const Widget& widget, const glm::vec2& offset)
{
	const auto& slider = widget.m_asset.getSprite(SPRITE_SLIDER);
	if (slider == nullptr)
		return;
	const auto& button = widget.m_family.getChildren()[BUTTON_BAR];
	const auto& clickable = button->m_clickable;

	const std::string state = clickable.isLocked() ? "locked" : clickable.isHovered() || clickable.isClicked() ? "hovered" : "normal";
	unsigned int frame = slider->getFrameIndex(state);
	if (frame == -1)
		frame = 0;

	const auto value = widget.m_data.get<float>(DATA_VALUE);
	const auto middle = widget.m_data.get<float>(DATA_MIDDLE);
	const auto limit = widget.m_data.get<glm::vec2>(DATA_LIMIT);
	const auto ratio = 0.5f * (value < middle ? (value - limit.x) / (middle - limit.x) : 2.0f - (limit.y - value) / (limit.y - middle));

	const auto& size = button->m_size.getSize() - slider->getFrame(frame).m_w;
	const auto& pos = button->m_pos.getPos() + offset;
	slider->render(frame, pos.x + ratio * size.x, pos.y);
}

void hen::gui::LoaderSlider::setLimit(Widget& widget, const glm::vec2& limit, float middle)
{
	widget.m_data.set<glm::vec2>(DATA_LIMIT, limit);
	widget.m_data.set<float>(DATA_MIDDLE, middle);
	setValue(widget, getValue(widget));
}
void hen::gui::LoaderSlider::setValue(Widget& widget, float value)
{
	const auto snap = widget.m_data.get<float>(DATA_SNAP);
	const auto limit = widget.m_data.get<glm::vec2>(DATA_LIMIT);
	const auto snappedValue = snap == 0.0f ? value : hen::math::round(value / snap) * snap;
	widget.m_data.set<float>(DATA_VALUE, hen::math::max(limit.x, hen::math::min(limit.y, snappedValue)));
	widget.m_clickable.invoke();
}
float hen::gui::LoaderSlider::getValue(const Widget & widget)
{
	return widget.m_data.get<float>(DATA_VALUE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void hen::gui::LoaderSlider::load(Widget& widget, const pugi::xml_node& node) const
{
	widget.setProcess(&LoaderSlider::process);
	widget.setRender(&LoaderSlider::render);

	widget.m_size.setMaxSize(widget.m_size.getMinSize());

	loadData(widget, node.child("data"));
	loadButtons(widget, node);
	loadCallback(widget);
}
void hen::gui::LoaderSlider::loadData(Widget& widget, const pugi::xml_node& node) const
{
	auto& data = widget.m_data;
	data.set(DATA_VALUE, node.attribute(DATA_VALUE).as_float());
	data.set(DATA_SNAP, node.attribute(DATA_SNAP).as_float());
	data.set(DATA_MIDDLE, node.attribute(DATA_MIDDLE).as_float());
	data.set(DATA_LIMIT, hen::string::as_vec2(node.attribute(DATA_LIMIT).as_string()));
}
void hen::gui::LoaderSlider::loadButtons(Widget& widget, const pugi::xml_node& node) const
{
	auto& resources = widget.getResources();
	auto& buttonDecrease = resources.createWidget(widget.getName() + "_DECREASE", &widget);
	auto& buttonIncrease = resources.createWidget(widget.getName() + "_INCREASE", &widget);
	auto& buttonBar = resources.createWidget(widget.getName() + "_BAR", &widget);

	LoaderButton loader;
	loader.load(buttonDecrease, pugi::xml_node{});
	loader.load(buttonIncrease, pugi::xml_node{});
	loader.load(buttonBar, pugi::xml_node{});
	loadButtonChange(widget, buttonDecrease, node, false);
	loadButtonChange(widget, buttonIncrease, node, true);
	loadButtonBar(widget, buttonBar, node);

	ComponentLink::Location location;
	if (widget.m_size.getSize().x >= widget.m_size.getSize().y)
		location = ComponentLink::Location::RIGHT_TOP;
	else
		location = ComponentLink::Location::BOTTOM_LEFT;

	buttonDecrease.m_link.setTarget(&widget);
	buttonDecrease.m_link.setLocation(ComponentLink::Location::TOP_LEFT);
	buttonBar.m_link.setTarget(&buttonDecrease);
	buttonBar.m_link.setLocation(location);
	buttonIncrease.m_link.setTarget(&buttonBar);
	buttonIncrease.m_link.setLocation(location);
}
void hen::gui::LoaderSlider::loadButtonChange(Widget& widget, Widget& button, const pugi::xml_node& node, bool increase) const
{
	const auto& size = widget.m_size.getMinSize();

	button.m_asset.addSprite(widget.m_asset.getPath(SPRITE_ICON), SPRITE_ICON);
	button.m_size.setMinSize(glm::vec2{ hen::math::min(size.x, size.y) });

	button.m_clickable.setInvoker([&]()
	{
		const auto value = widget.m_data.get<float>(DATA_VALUE);
		const auto snap = widget.m_data.get<float>(DATA_SNAP);
		setValue(widget, value + snap * (increase ? 1.0f : -1.0f));
	});
}
void hen::gui::LoaderSlider::loadButtonBar(const Widget& widget, Widget& button, const pugi::xml_node& node) const
{
	const auto& size = widget.m_size.getMinSize();
	if (size.x >= size.y)
		button.m_size.setMinSize(glm::vec2{ size.x - 2.0f * size.y, size.y });
	else
		button.m_size.setMinSize(glm::vec2{ size.x, size.y - 2.0f * size.x });
	button.setRender([](const hen::gui::Widget&, const glm::vec2&, float) {});
}
void hen::gui::LoaderSlider::loadCallback(Widget& widget) const
{
	widget.m_clickable.setInvoker([&]()
	{
		const auto& script = widget.m_script.get(SCRIPT_CHANGE);
		if (!script.empty())
		{
			const auto& value = widget.m_data.get<float>(DATA_VALUE);
			widget.getResources().getScript().executeScript(script + "(" + std::to_string(value) + ")");
		}
	});
}
