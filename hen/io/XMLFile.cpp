
#include "hen/io/XMLFile.h"

#include <Log.h>

pugi::xml_document& hen::io::XMLFile::open()
{
	m_handle.reset();
	const auto& result = m_handle.load_file(m_file.getPath().c_str());
	if (result.status != pugi::status_ok)
	{
		LOG_WARNING << "Error while parsing file " + m_file.getPath();
		LOG_WARNING << result.description();
	}
	return m_handle;
}
