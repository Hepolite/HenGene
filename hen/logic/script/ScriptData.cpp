
#include "hen/logic/script/ScriptData.h"

#include "hen/core/Core.h"
#include "hen/logic/script/ScriptHelper.h"
#include "hen/logic/state/StateManager.h"
#include "hen/ui/gui/internal/GuiBase.h"
#include "hen/util/MathEnum.h"

#include <glm/vec3.hpp>
#include <Log.h>

#include <string>

namespace scriptdata
{
	using namespace hen;

	inline void debug(const std::string& msg) { LOG_DEBUG << msg; }
	inline void info(const std::string& msg) { LOG_INFO << msg; }
	inline void warn(const std::string& msg) { LOG_WARNING << msg; }

	template<typename T>
	void addGlmGeneric(script::ScriptHelper& helper)
	{
		helper.addFunction<T&, T, const T&>(&T::operator=, "=");
		helper.addFunction<T&, T, const T&>(&T::operator+=, "+=");
		helper.addFunction<T&, T, const T&>(&T::operator-=, "-=");
		helper.addFunction<T&, T, const T&>(&T::operator*=, "*=");
		helper.addFunction<T&, T, const T&>(&T::operator/=, "/=");

		helper.addFunction<T, const T&, const T&>(&glm::operator+, "+");
		helper.addFunction<T, const T&, const T&>(&glm::operator-, "-");
		helper.addFunction<T, const T&, const T&>(&glm::operator*, "*");
		helper.addFunction<T, const T&, const T&>(&glm::operator/, "/");
	}
	template<typename T>
	void addGlmVec2(script::ScriptHelper& helper, const std::string& name)
	{
		helper.addType<glm::tvec2<T>>(name);
		helper.addConstructor<glm::tvec2<T>()>(name);
		helper.addConstructor<glm::tvec2<T>(const glm::tvec4<T>&)>(name);
		helper.addConstructor<glm::tvec2<T>(const glm::tvec3<T>&)>(name);
		helper.addConstructor<glm::tvec2<T>(const glm::tvec2<T>&)>(name);
		helper.addConstructor<glm::tvec2<T>(T, T)>(name);
		helper.addAttribute(&glm::tvec2<T>::x, "x");
		helper.addAttribute(&glm::tvec2<T>::y, "y");
		addGlmGeneric<glm::tvec2<T>>(helper);
	}
	template<typename T>
	void addGlmVec3(script::ScriptHelper& helper, const std::string& name)
	{
		helper.addType<glm::tvec3<T>>(name);
		helper.addConstructor<glm::tvec3<T>()>(name);
		helper.addConstructor<glm::tvec3<T>(const glm::tvec4<T>&)>(name);
		helper.addConstructor<glm::tvec3<T>(const glm::tvec3<T>&)>(name);
		helper.addConstructor<glm::tvec3<T>(const glm::tvec2<T>&, T)>(name);
		helper.addConstructor<glm::tvec3<T>(T, T, T)>(name);
		helper.addAttribute(&glm::tvec3<T>::x, "x");
		helper.addAttribute(&glm::tvec3<T>::y, "y");
		helper.addAttribute(&glm::tvec3<T>::z, "z");
		addGlmGeneric<glm::tvec3<T>>(helper);
	}
	template<typename T>
	void addGlmVec4(script::ScriptHelper& helper, const std::string& name)
	{
		helper.addType<glm::tvec4<T>> (name);
		helper.addConstructor<glm::tvec4<T>()>(name);
		helper.addConstructor<glm::tvec4<T>(const glm::tvec4<T>&)>(name);
		helper.addConstructor<glm::tvec4<T>(const glm::tvec3<T>&, T)>(name);
		helper.addConstructor<glm::tvec4<T>(const glm::tvec2<T>&, T, T)>(name);
		helper.addConstructor<glm::tvec4<T>(const glm::tvec2<T>&, const glm::tvec2<T>&)>(name);
		helper.addConstructor<glm::tvec4<T>(T, T, T, T)>(name);
		helper.addAttribute(&glm::tvec4<T>::x, "x");
		helper.addAttribute(&glm::tvec4<T>::y, "y");
		helper.addAttribute(&glm::tvec4<T>::z, "z");
		helper.addAttribute(&glm::tvec4<T>::w, "w");
		addGlmGeneric<glm::tvec4<T>>(helper);
	}

	void addCore(script::ScriptHelper& helper)
	{
		helper.addFunction(&Core::stop, "terminate");
	}
	void addGui(script::ScriptHelper& helper)
	{
		helper.addFunction(&gui::GuiBase::hasWidget, "hasWidget");
		helper.addFunction(&gui::GuiBase::getWidget, "getWidget");

		helper.addAttribute(&gui::Widget::m_clickable, "clickable");
		helper.addFunction(&gui::Widget::setVisible, "setVisible");
		helper.addFunction(&gui::Widget::isVisible, "isVisible");
		helper.addFunction(&gui::Widget::click, "click");

		helper.addFunction(&gui::ComponentClickable::isLocked, "isLocked");
		helper.addFunction(&gui::ComponentClickable::setLocked, "setLocked");
	}
	void addLogging(script::ScriptHelper& helper)
	{
		helper.addFunction(&info, "LOG_INFO");
		helper.addFunction(&warn, "LOG_WARN");
		helper.addFunction(&debug, "LOG_DEBUG");
	}
	void addMath(script::ScriptHelper& helper)
	{
		addGlmVec2<float>(helper, "vec2");
		addGlmVec2<double>(helper, "dvec2");
		addGlmVec2<int>(helper, "ivec2");
		addGlmVec2<unsigned int>(helper, "uvec2");

		addGlmVec3<float>(helper, "vec3");
		addGlmVec3<double>(helper, "dvec3");
		addGlmVec3<int>(helper, "ivec3");
		addGlmVec3<unsigned int>(helper, "uvec3");

		addGlmVec4<float>(helper, "vec4");
		addGlmVec4<double>(helper, "dvec4");
		addGlmVec4<int>(helper, "ivec4");
		addGlmVec4<unsigned int>(helper, "uvec4");

		helper.addEnum<math::Axis>("Axis", {
			{ math::Axis::X, "AXIS_X" },
			{ math::Axis::Y, "AXIS_Y" },
			{ math::Axis::Z, "AXIS_Z" }
		});
	}
	void addStateManager(script::ScriptHelper& helper)
	{
		helper.addGlobalVariable(&Core::getStateManager(), "StateManager");
		helper.addFunction(&state::StateManager::addState, "addState");
		helper.addFunction(&state::StateManager::setState, "setState");
		helper.addFunction(&state::StateManager::removeState, "removeState");
	}
}

void hen::script::ScriptData::setup() const
{
	ScriptHelper::addScriptData([](ScriptHelper& helper)
	{
		scriptdata::addCore(helper);
		scriptdata::addGui(helper);
		scriptdata::addLogging(helper);
		scriptdata::addMath(helper);
		scriptdata::addStateManager(helper);
	});
}
