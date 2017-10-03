
#include "hen/logic/script/ScriptHelper.h"

#include <Log.h>

std::vector<std::function<void(hen::script::ScriptHelper&)>> hen::script::ScriptHelper::m_scriptData;

void hen::script::ScriptHelper::addScriptData(std::function<void(ScriptHelper&)>&& data)
{
	m_scriptData.push_back(data);
}
void hen::script::ScriptHelper::applyScriptData()
{
	for (const auto& data : m_scriptData)
		data(*this);
}

void hen::script::ScriptHelper::info(const std::string& msg)
{
	LOG_INFO << msg;
}
void hen::script::ScriptHelper::warn(const std::string& msg)
{
	LOG_WARNING << msg;
}
