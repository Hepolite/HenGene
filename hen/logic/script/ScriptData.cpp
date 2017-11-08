
#include "hen/logic/script/ScriptData.h"

#include "hen/core/Core.h"
#include "hen/logic/script/ScriptHelper.h"
#include "hen/logic/state/StateManager.h"
#include "hen/ui/gui/internal/GuiBase.h"
#include "hen/util/MathEnum.h"
#include "hen/util/MathLib.h"

#include <glm/vec3.hpp>
#include <Log.h>

#include <string>

namespace scriptdata
{
	using namespace hen;
	using namespace glm;

	inline void debug(const std::string& msg) { LOG_DEBUG << msg; }
	inline void info(const std::string& msg) { LOG_INFO << msg; }
	inline void warn(const std::string& msg) { LOG_WARNING << msg; }

	template<typename Vec, typename Type>
	void addGlmVecGeneric(script::ScriptHelper& helper)
	{
		helper.addFunction<bool, const Vec&, const Vec&>(&operator==, "==");
		helper.addFunction<bool, const Vec&, const Vec&>(&operator!=, "!=");

		helper.addFunction<Vec&, Vec>(&Vec::operator++, "++");
		helper.addFunction<Vec, Vec, int>(&Vec::operator++, "++");
		helper.addFunction<Vec&, Vec>(&Vec::operator--, "--");
		helper.addFunction<Vec, Vec, int>(&Vec::operator--, "--");

		helper.addFunction<Vec, const Vec&>(&operator+, "+");
		helper.addFunction<Vec, const Vec&>(&operator-, "-");

		helper.addFunction<Vec, const Vec&, const Vec&>(&operator+, "+");
		helper.addFunction<Vec, const Vec&, const Vec&>(&operator-, "-");
		helper.addFunction<Vec, const Vec&, const Vec&>(&operator*, "*");
		helper.addFunction<Vec, const Vec&, const Vec&>(&operator/, "/");
		helper.addFunction<Vec, Type, const Vec&>(&operator+, "+");
		helper.addFunction<Vec, Type, const Vec&>(&operator-, "-");
		helper.addFunction<Vec, Type, const Vec&>(&operator*, "*");
		helper.addFunction<Vec, Type, const Vec&>(&operator/, "/");
		helper.addFunction<Vec, const Vec&, Type>(&operator+, "+");
		helper.addFunction<Vec, const Vec&, Type>(&operator-, "-");
		helper.addFunction<Vec, const Vec&, Type>(&operator*, "*");
		helper.addFunction<Vec, const Vec&, Type>(&operator/, "/");
	}
	template<typename Vec, typename Vec2, typename Type>
	void addGlmVecOperators(script::ScriptHelper& helper)
	{
		helper.addFunction<Vec&, Vec, const Vec2&>(&Vec::operator=, "=");

		helper.addFunction<Vec&, Vec, const Vec2&>(&Vec::operator+=, "+=");
		helper.addFunction<Vec&, Vec, const Vec2&>(&Vec::operator-=, "-=");
		helper.addFunction<Vec&, Vec, const Vec2&>(&Vec::operator*=, "*=");
		helper.addFunction<Vec&, Vec, const Vec2&>(&Vec::operator/=, "/=");
		helper.addFunction<Vec&, Vec, Type>(&Vec::operator+=, "+=");
		helper.addFunction<Vec&, Vec, Type>(&Vec::operator-=, "-=");
		helper.addFunction<Vec&, Vec, Type>(&Vec::operator*=, "*=");
		helper.addFunction<Vec&, Vec, Type>(&Vec::operator/=, "/=");
	}
	template<typename T, typename U>
	void addGlmVec2Data(script::ScriptHelper& helper, const std::string& name)
	{
		helper.addConstructor<tvec2<T>(const tvec4<U>&)>(name);
		helper.addConstructor<tvec2<T>(const tvec3<U>&)>(name);
		helper.addConstructor<tvec2<T>(const tvec2<U>&)>(name);
	}
	template<typename T>
	void addGlmVec2(script::ScriptHelper& helper, const std::string& name)
	{
		helper.addType<tvec2<T>>(name);
		helper.addConstructor<tvec2<T>()>(name);
		helper.addConstructor<tvec2<T>(T, T)>(name);
		helper.addConstructor<tvec2<T>(T)>(name);

		helper.addAttribute(&tvec2<T>::x, "x");
		helper.addAttribute(&tvec2<T>::y, "y");

		addGlmVec2Data<T, double>(helper, name);
		addGlmVec2Data<T, float>(helper, name);
		addGlmVec2Data<T, int>(helper, name);

		addGlmVecGeneric<tvec2<T>, T>(helper);
		addGlmVecOperators<tvec2<T>, glm::tvec2<double>, double>(helper);
		addGlmVecOperators<tvec2<T>, glm::tvec2<float>, float>(helper);
		addGlmVecOperators<tvec2<T>, glm::tvec2<int>, int>(helper);

		helper.addFunction<ivec2, const tvec2<T>&>(&math::round, "round");
		helper.addFunction<ivec2, const tvec2<T>&>(&math::floor, "floor");
		helper.addFunction<ivec2, const tvec2<T>&>(&math::ceil, "ceil");
	}
	template<typename T, typename U>
	void addGlmVec3Data(script::ScriptHelper& helper, const std::string& name)
	{
		helper.addConstructor<tvec3<T>(const tvec4<U>&)>(name);
		helper.addConstructor<tvec3<T>(const tvec3<U>&)>(name);
		helper.addConstructor<tvec3<T>(const tvec2<U>&, U)>(name);
	}
	template<typename T>
	void addGlmVec3(script::ScriptHelper& helper, const std::string& name)
	{
		helper.addType<tvec3<T>>(name);
		helper.addConstructor<tvec3<T>()>(name);
		helper.addConstructor<tvec3<T>(T, T, T)>(name);
		helper.addConstructor<tvec3<T>(T)>(name);

		helper.addAttribute(&tvec3<T>::x, "x");
		helper.addAttribute(&tvec3<T>::y, "y");
		helper.addAttribute(&tvec3<T>::z, "z");

		addGlmVec3Data<T, double>(helper, name);
		addGlmVec3Data<T, float>(helper, name);
		addGlmVec3Data<T, int>(helper, name);

		addGlmVecGeneric<tvec3<T>, T>(helper);
		addGlmVecOperators<tvec3<T>, glm::tvec3<double>, double>(helper);
		addGlmVecOperators<tvec3<T>, glm::tvec3<float>, float>(helper);
		addGlmVecOperators<tvec3<T>, glm::tvec3<int>, int>(helper);

		helper.addFunction<ivec3, const tvec3<T>&>(&math::round, "round");
		helper.addFunction<ivec3, const tvec3<T>&>(&math::floor, "floor");
		helper.addFunction<ivec3, const tvec3<T>&>(&math::ceil, "ceil");
	}
	template<typename T, typename U>
	void addGlmVec4Data(script::ScriptHelper& helper, const std::string& name)
	{
		helper.addConstructor<tvec4<T>(const tvec4<U>&)>(name);
		helper.addConstructor<tvec4<T>(const tvec3<U>&, U)>(name);
		helper.addConstructor<tvec4<T>(const tvec2<U>&, U, U)>(name);
	}
	template<typename T>
	void addGlmVec4(script::ScriptHelper& helper, const std::string& name)
	{
		helper.addType<tvec4<T>> (name);
		helper.addConstructor<tvec4<T>()>(name);
		helper.addConstructor<tvec4<T>(T, T, T, T)>(name);
		helper.addConstructor<tvec4<T>(T)>(name);

		helper.addAttribute(&tvec4<T>::x, "x");
		helper.addAttribute(&tvec4<T>::y, "y");
		helper.addAttribute(&tvec4<T>::z, "z");
		helper.addAttribute(&tvec4<T>::w, "w");

		addGlmVec4Data<T, double>(helper, name);
		addGlmVec4Data<T, float>(helper, name);
		addGlmVec4Data<T, int>(helper, name);

		addGlmVecGeneric<tvec4<T>, T>(helper);
		addGlmVecOperators<tvec4<T>, glm::tvec4<double>, double>(helper);
		addGlmVecOperators<tvec4<T>, glm::tvec4<float>, float>(helper);
		addGlmVecOperators<tvec4<T>, glm::tvec4<int>, int>(helper);

		helper.addFunction<ivec4, const tvec4<T>&>(&math::round, "round");
		helper.addFunction<ivec4, const tvec4<T>&>(&math::floor, "floor");
		helper.addFunction<ivec4, const tvec4<T>&>(&math::ceil, "ceil");
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
		addGlmVec3<float>(helper, "vec3");
		addGlmVec4<float>(helper, "vec4");
		addGlmVec2<double>(helper, "dvec2");
		addGlmVec3<double>(helper, "dvec3");
		addGlmVec4<double>(helper, "dvec4");
		addGlmVec2<int>(helper, "ivec2");
		addGlmVec3<int>(helper, "ivec3");
		addGlmVec4<int>(helper, "ivec4");

		helper.addFunction<vec3, float, float>(&math::toCartesian, "toCartesian");
		helper.addFunction<vec3, const vec2&>(&math::toCartesian, "toCartesian");
		helper.addFunction<vec3, const vec3&>(&math::toCartesian, "toCartesian");
		helper.addFunction<vec2, float, float, float>(&math::toSpherical, "toSpherical");
		helper.addFunction<vec2, const vec3&>(&math::toSpherical, "toSpherical");

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
