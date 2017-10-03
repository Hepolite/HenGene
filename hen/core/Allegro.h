
#pragma once

#include <functional>
#include <string>

namespace hen
{
	namespace core
	{
		class Allegro
		{
		public:
			Allegro();
			~Allegro();

			inline bool hasStartupErrors() const { return m_hasStartupErrors; }
			inline bool isInitialized() const { return m_isInitialized; }

		private:
			bool install(const std::function<void()>& func, const std::string& succeeded) const;
			bool install(const std::function<bool()>& func, const std::string& succeeded, const std::string& failed) const;

			bool m_hasStartupErrors = false;
			bool m_isInitialized = false;
		};
	}
}