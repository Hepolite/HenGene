
#pragma once

#include "hen/io/File.h"

#include <extern/pugixml/pugixml.hpp>

namespace hen
{
	namespace io
	{
		class XMLFile
		{
		public:
			XMLFile() = default;
			XMLFile(const char* file) : m_file(file) {}
			XMLFile(const io::File& file) : m_file(file) {}
			~XMLFile() = default;

			pugi::xml_document& open();

		private:
			pugi::xml_document m_handle;
			io::File m_file;
		};
	}
}