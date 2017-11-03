
#include "hen/logic/script/Script.h"

#include "hen/core/Core.h"
#include "hen/io/File.h"
#include "hen/logic/script/ScriptHelper.h"
#include "hen/logic/state/StateManager.h"
#include "hen/ui/gui/internal/GuiBase.h"
#include "hen/ui/gui/Widget.h"
#include "hen/util/MathEnum.h"

#include <glm/glm.hpp>
#include <Log.h>

#include <iostream>
#include <sstream>

namespace hen
{
	namespace script
	{
		template<typename T>
		inline T get(chaiscript::ChaiScript& script, const std::string& expression, const T& def)
		{
			try
			{
				return script.eval<T>(expression);
			}
			catch (const std::exception&)
			{
				return def;
			}
		}

		inline void debug(const std::string& msg) { LOG_DEBUG << msg; }
		inline void info(const std::string& msg) { LOG_INFO << msg; }
		inline void warn(const std::string& msg) { LOG_WARNING << msg; }

		std::string parse(const std::string& path)
		{
			std::istringstream stream{ path };
			std::stringstream buffer;
			for (std::string line; std::getline(stream, line, '\r'); )
			{
				if (line.find("#include ") != std::string::npos)
				{
					auto first = line.find_first_of("\"");
					auto last = line.find_last_of("\"");
					if (first != std::string::npos && last != std::string::npos)
						buffer << parse(io::File{ line.substr(first + 1, last - first - 1) }.read());
				}
				else
					buffer << line << std::endl;
			}
			return buffer.str();
		}
	}
}

class hen::script::Script::Internal
{
public:
	chaiscript::ChaiScript m_handle;
};

hen::script::Script::Script()
{
	m_internal = new Internal;
	registerDefaultFunctionality();
}
hen::script::Script::~Script()
{
	delete m_internal;
}

chaiscript::ChaiScript& hen::script::Script::getHandle()
{
	return m_internal->m_handle;
}

void hen::script::Script::registerDefaultFunctionality()
{
	ScriptHelper helper{ *this };
	helper.applyScriptData();

	// Core
	helper.addFunction(&Core::stop, "terminate");

	// State manager
	helper.addGlobalVariable(&Core::getStateManager(), "StateManager");
	helper.addFunction(&state::StateManager::addState, "addState");
	helper.addFunction(&state::StateManager::setState, "setState");
	helper.addFunction(&state::StateManager::removeState, "removeState");

	// Gui
	helper.addFunction(&gui::GuiBase::hasWidget, "hasWidget");
	helper.addFunction(&gui::GuiBase::getWidget, "getWidget");

	helper.addAttribute(&gui::Widget::m_clickable, "clickable");
	helper.addFunction(&gui::Widget::setVisible, "setVisible");
	helper.addFunction(&gui::Widget::isVisible, "isVisible");
	helper.addFunction(&gui::Widget::click, "click");

	helper.addFunction(&gui::ComponentClickable::isLocked, "isLocked");
	helper.addFunction(&gui::ComponentClickable::setLocked, "setLocked");

	// Math utility
	helper.addType<glm::ivec3>("ivec3");
	helper.addConstructor<glm::ivec3()>("ivec3");
	helper.addConstructor<glm::ivec3(glm::ivec3)>("ivec3");
	helper.addConstructor<glm::ivec3(glm::ivec2, int)>("ivec3");
	helper.addConstructor<glm::ivec3(int, int, int)>("ivec3");
	helper.addAttribute(&glm::ivec3::x, "x");
	helper.addAttribute(&glm::ivec3::y, "y");
	helper.addAttribute(&glm::ivec3::z, "z");

	helper.addType<glm::ivec4>("ivec4");
	helper.addConstructor<glm::ivec4()>("ivec4");
	helper.addConstructor<glm::ivec4(glm::ivec4)>("ivec4");
	helper.addConstructor<glm::ivec4(glm::ivec3, int)>("ivec4");
	helper.addConstructor<glm::ivec4(glm::ivec2, int, int)>("ivec4");
	helper.addConstructor<glm::ivec4(glm::ivec2, glm::ivec2)>("ivec4");
	helper.addConstructor<glm::ivec4(int, int, int, int)>("ivec4");
	helper.addAttribute(&glm::ivec4::x, "x");
	helper.addAttribute(&glm::ivec4::y, "y");
	helper.addAttribute(&glm::ivec4::z, "z");
	helper.addAttribute(&glm::ivec4::w, "w");

	helper.addEnum<math::Axis>("Axis", {
		{ math::Axis::X, "AXIS_X" },
		{ math::Axis::Y, "AXIS_Y" },
		{ math::Axis::Z, "AXIS_Z" }
	});

	// Logging
	helper.addFunction(&info, "LOG_INFO");
	helper.addFunction(&warn, "LOG_WARN");
	helper.addFunction(&debug, "LOG_DEBUG");
}

bool hen::script::Script::executeScript(const std::string& script) const
{
	try
	{
		m_internal->m_handle.eval(script);
		return true;
	}
	catch (const std::exception& e)
	{
		LOG_WARNING << "Error in script " << std::endl << script << std::endl << e.what();
	}
	return false;
}
bool hen::script::Script::executeFile(const io::File& file) const
{
	if (!file.exists())
	{
		LOG_WARNING << "Attempted to execute nonexisting script file " << file.getPath();
		return false;
	}
	return executeScript(parse(file.read()));
}

bool hen::script::Script::getBool(const std::string& expression, bool def) const
{
	return get(m_internal->m_handle, expression, def);
}
double hen::script::Script::getDouble(const std::string& expression, double def) const
{
	return get(m_internal->m_handle, expression, def);
}
float hen::script::Script::getFloat(const std::string& expression, float def) const
{
	return get(m_internal->m_handle, expression, def);
}
int hen::script::Script::getInt(const std::string& expression, int def) const
{
	return get(m_internal->m_handle, expression, def);
}
std::string hen::script::Script::getString(const std::string& expression, const std::string& def) const
{
	return get(m_internal->m_handle, expression, def);
}
