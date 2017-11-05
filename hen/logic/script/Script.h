
#pragma once

#include "hen/io/File.h"

#include <functional>
#include <memory>
#include <string>

namespace chaiscript
{
	class ChaiScript;
}

namespace hen
{
	namespace script
	{
		class Script
		{
		public:
			Script();
			Script(const Script&) = delete;
			Script(Script&&) = delete;
			~Script();

			Script& operator=(const Script&) = delete;
			Script& operator=(Script&&) = delete;

			chaiscript::ChaiScript& getHandle();
			
			bool executeScript(const std::string& script) const;
			bool executeFile(const io::File& file) const;

			bool getBool(const std::string& expression, bool def = false) const;
			double getDouble(const std::string& expression, double def = 0.0) const;
			float getFloat(const std::string& expression, float def = 0.0f) const;
			int getInt(const std::string& expression, int def = 0) const;
			std::string getString(const std::string& expression, const std::string& def = "") const;

		private:
			class Internal;
			std::unique_ptr<Internal> m_internal;
		};
	}
}