
#pragma once

namespace hen
{
	namespace gui
	{
		// Widget types
		constexpr char* TYPE_BUTTON = "button";
		constexpr char* TYPE_CHECKBOX = "checkbox";
		constexpr char* TYPE_LABEL = "label";
		constexpr char* TYPE_PANEL = "panel";
		constexpr char* TYPE_RADIO = "radio";
		constexpr char* TYPE_SLIDER = "slider";
		constexpr char* TYPE_TEXTBOX = "textbox";
		constexpr char* TYPE_TEXTFIELD = "textfield";
		constexpr char* TYPE_WINDOW = "window";

		// Widget components
		constexpr char* COMPONENT_BORDER = "border";
		constexpr char* COMPONENT_CLICKABLE = "clickable";
		constexpr char* COMPONENT_DATA = "data";
		constexpr char* COMPONENT_GROUP = "group";
		constexpr char* COMPONENT_LINK = "link";
		constexpr char* COMPONENT_POSITION = "position";
		constexpr char* COMPONENT_SCRIPT = "script";
		constexpr char* COMPONENT_SIZE = "size";
		constexpr char* COMPONENT_SPRITE = "sprite";
		constexpr char* COMPONENT_TEXT = "text";
		constexpr char* COMPONENT_WIDGET = "widget";

		// Component attributes
		constexpr char* ATTRIBUTE_HEADER_VISIBLE = "visible";

		constexpr char* ATTRIBUTE_BORDER_ALL = "all";
		constexpr char* ATTRIBUTE_BORDER_INNER = "inner";
		constexpr char* ATTRIBUTE_BORDER_INNER_BOTTOM = "inner_bottom";
		constexpr char* ATTRIBUTE_BORDER_INNER_LEFT = "inner_left";
		constexpr char* ATTRIBUTE_BORDER_INNER_RIGHT = "inner_right";
		constexpr char* ATTRIBUTE_BORDER_INNER_TOP = "inner_top";
		constexpr char* ATTRIBUTE_BORDER_OUTER = "outer";
		constexpr char* ATTRIBUTE_BORDER_OUTER_BOTTOM = "outer_bottom";
		constexpr char* ATTRIBUTE_BORDER_OUTER_LEFT = "outer_left";
		constexpr char* ATTRIBUTE_BORDER_OUTER_RIGHT = "outer_right";
		constexpr char* ATTRIBUTE_BORDER_OUTER_TOP = "outer_top";

		constexpr char* ATTRIBUTE_CLICKABLE_ACTIVE = "active";
		constexpr char* ATTRIBUTE_CLICKABLE_INVERTED = "inverted";
		constexpr char* ATTRIBUTE_CLICKABLE_LOCKED = "locked";

		constexpr char* ATTRIBUTE_DATA_LIMIT = "limit";
		constexpr char* ATTRIBUTE_DATA_MIDDLE = "middle";
		constexpr char* ATTRIBUTE_DATA_SNAP = "snap";
		constexpr char* ATTRIBUTE_DATA_VALUE = "value";

		constexpr char* ATTRIBUTE_GROUP_LEADER = "leader";

		constexpr char* ATTRIBUTE_LINK_TARGET = "target";
		constexpr char* ATTRIBUTE_LINK_LOCATION = "location";

		constexpr char* ATTRIBUTE_POSITION_OFFSET = "offset";

		constexpr char* ATTRIBUTE_SIZE_SIZE = "size";
		constexpr char* ATTRIBUTE_SIZE_MIN = "min";
		constexpr char* ATTRIBUTE_SIZE_MAX = "max";

		constexpr char* ATTRIBUTE_TEXT_ALIGN = "align";
		constexpr char* ATTRIBUTE_TEXT_FONT = "font";
		constexpr char* ATTRIBUTE_TEXT_HEIGHT = "height";
		constexpr char* ATTRIBUTE_TEXT_WIDTH = "width";

		constexpr char* ATTRIBUTE_WIDGET_NAME = "name";
		constexpr char* ATTRIBUTE_WIDGET_TYPE = "type";

		// Attribute special values
		const std::string DATA_ACTIVE = "active";
		const std::string DATA_INVERTED = "inverted";
		const std::string DATA_LIMIT = "limit";
		const std::string DATA_MIDDLE = "middle";
		const std::string DATA_RENDER_FLAGS = "render_flags";
		const std::string DATA_RENDER_ROTATION = "render_rotation";
		const std::string DATA_SNAP = "snap";
		const std::string DATA_TEXT = "text";
		const std::string DATA_VALUE = "value";

		const std::string LINK_PARENT = "parent";
		const std::string LINK_TOP_LEFT = "top_left";
		const std::string LINK_TOP = "top";
		const std::string LINK_TOP_RIGHT = "top_right";
		const std::string LINK_LEFT_TOP = "left_top";
		const std::string LINK_RIGHT_TOP = "right_top";
		const std::string LINK_LEFT = "left";
		const std::string LINK_CENTER = "center";
		const std::string LINK_RIGHT = "right";
		const std::string LINK_LEFT_BOTTOM = "left_bottom";
		const std::string LINK_RIGHT_BOTTOM = "right_bottom";
		const std::string LINK_BOTTOM_LEFT = "bottom_left";
		const std::string LINK_BOTTOM = "bottom";
		const std::string LINK_BOTTOM_RIGHT = "bottom_right";

		const std::string SCRIPT_CHANGE = "change";
		const std::string SCRIPT_CLICK = "click";

		const std::string SPRITE_BACKGROUND = "background";
		const std::string SPRITE_ICON = "icon";
		const std::string SPRITE_ICON_STATE_LOCKED = "locked";
		const std::string SPRITE_ICON_STATE_HOVERED = "hovered";
		const std::string SPRITE_ICON_STATE_NORMAL = "normal";
		const std::string SPRITE_ICON_STATE_ACTIVE = "active";
		const std::string SPRITE_ICON_STATE_INACTIVE = "inactive";
		const std::string SPRITE_SLIDER = "slider";

		const std::string TEXT_ALIGN_CENTER = "center";
		const std::string TEXT_ALIGN_RIGHT = "right";
		const std::string TEXT_ALIGN_LEFT = "left";
	}
}