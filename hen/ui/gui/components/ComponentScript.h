
#pragma once

#include <string>
#include <unordered_map>

namespace hen
{
	namespace gui
	{
		class ComponentScript
		{
		public:
			inline void set(const std::string& name, const std::string& script) { m_scripts[name] = script; }
			inline std::string get(const std::string& name) const
			{
				const auto& result = m_scripts.find(name);
				return result == m_scripts.end() ? "" : result->second;
			}

		private:
			std::unordered_map<std::string, std::string> m_scripts;
		};
	}
}