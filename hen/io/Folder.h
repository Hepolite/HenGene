
#pragma once

#include "hen/io/File.h"

#include <string>
#include <vector>

namespace hen
{
	namespace io
	{
		class Folder
		{
		public:
			Folder(const char* path);
			Folder(const std::string& path);

			bool exists() const;

			inline std::string getPath() const { return m_path; }
			inline std::string getName() const { return m_name; }

			std::vector<Folder> getFolders() const;
			std::vector<File> getFiles() const;

		private:
			std::string m_path;
			std::string m_name;
		};
	}
}