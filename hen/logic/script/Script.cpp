
#include "hen/logic/script/Script.h"

#include "hen/logic/script/ScriptHelper.h"

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
	m_internal = std::make_unique<Internal>();
	ScriptHelper{ *this }.applyScriptData();
}
hen::script::Script::~Script() {}

chaiscript::ChaiScript& hen::script::Script::getHandle()
{
	return m_internal->m_handle;
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
