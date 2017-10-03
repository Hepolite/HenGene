
#pragma once

#include <string>

namespace hen
{
	namespace io
	{
		class File
		{
		public:
			File(const char* path);
			File(const std::string& path);

			bool exists() const;
			bool create() const;
			bool erase() const;
			std::string read() const;

			inline std::string getPath() const { return m_path; }
			inline std::string getName() const { return m_name; }
			inline std::string getType() const { return m_type; }

		private:
			std::string m_path;
			std::string m_name;
			std::string m_type;
		};
	}
}