
#pragma once

#include "hen/logic/script/Script.h"

#include "chaiscript/chaiscript.hpp"

#include <string>
#include <vector>

namespace hen
{
	namespace script
	{
		class ScriptHelper
		{
		public:
			ScriptHelper(Script& script) : m_script(script) {}
			ScriptHelper(const ScriptHelper&) = delete;
			ScriptHelper(ScriptHelper&&) = delete;
			~ScriptHelper() = default;

			ScriptHelper& operator=(const ScriptHelper&) = delete;
			ScriptHelper& operator=(ScriptHelper&&) = delete;

			static void addScriptData(std::function<void(ScriptHelper&)>&& data);
			void applyScriptData();

			template<typename T>
			inline void addType(const std::string& name)
			{
				m_script.getHandle().add(chaiscript::user_type<T>(), name);
			}
			template<typename Parent, typename Child>
			inline void addRelation()
			{
				m_script.getHandle().add(chaiscript::base_class<Parent, Child>());
			}

			template<typename T>
			inline void addVariable(T&& variable, const std::string& name)
			{
				m_script.getHandle().add(chaiscript::var(variable), name);
			}
			template<typename T>
			inline void addGlobalVariable(T&& variable, const std::string& name)
			{
				m_script.getHandle().add_global(chaiscript::var(variable), name);
			}
			template<typename T>
			inline void addConstGlobalVariable(const T& variable, const std::string& name)
			{
				m_script.getHandle().add_global_const(chaiscript::const_var(variable), name);
			}
			template<typename T>
			inline void addAttribute(T&& attribute, const std::string& name)
			{
				m_script.getHandle().add(chaiscript::fun(attribute), name);
			}

			template<typename Ret, typename ...Param>
			inline void addFunction(Ret(*function)(Param...), const std::string& name)
			{
				m_script.getHandle().add(chaiscript::fun(function), name);
			}
			template<typename Ret, typename Class, typename ...Param>
			inline void addFunction(Ret(Class::*function)(Param...), const std::string& name)
			{
				m_script.getHandle().add(chaiscript::fun(function), name);
			}
			template<typename Ret, typename Class, typename ...Param>
			inline void addFunction(Ret(Class::*function)(Param...) const, const std::string& name)
			{
				m_script.getHandle().add(chaiscript::fun(function), name);
			}
			template<typename T>
			inline void addConstructor(const std::string& name)
			{
				m_script.getHandle().add(chaiscript::constructor<T>(), name);
			}

			template<typename Enum>
			inline void addEnum(const std::string& name, const std::vector<std::pair<Enum, std::string>>& pairs)
			{
				chaiscript::ModulePtr ptr = std::make_shared<chaiscript::Module>();
				chaiscript::utility::add_class<math::Axis>(*ptr, name, pairs);
				m_script.getHandle().add(ptr);
			}


			template<typename Ret, typename ...Param>
			inline std::function<Ret(Param...)> getFunction(const std::string& name) const
			{
				try
				{
					return m_script.getHandle().eval<std::function<Ret(Param...)>>(name);
				}
				catch (const std::exception& e)
				{
					warn("Unable to obtain function " + name);
					warn(e.what());
					return [](Param...) -> Ret {};
				}
			}
			template<typename T>
			inline T getValue(const std::string& expression, const T& def = T{ 0 }) const
			{
				try
				{
					return m_script.getHandle().eval<T>(expression);
				}
				catch (const std::exception&)
				{
					return def;
				}
			}

			template<typename Ret, typename ...Param>
			inline bool executeShell(const std::function<Ret(Param...)>& shell, Param& ...params) const
			{
				if (shell == nullptr)
				{
					warn("Attempted to execute nonexisting shell");
					return false;
				}
				try
				{
					shell(params...);
					return true;
				}
				catch (const std::exception& e)
				{
					warn("Error while executing shell");
					warn(e.what());
				}
				return false;
			}
			inline bool executeScript(const std::string& script) const { return m_script.executeScript(script); }
			inline bool executeFile(const io::File& file) const { return m_script.executeFile(file); }

		private:
			void info(const std::string& msg) const;
			void warn(const std::string& msg) const;

			static std::vector<std::function<void(ScriptHelper&)>> m_scriptData;

			Script& m_script;
		};
	}
}