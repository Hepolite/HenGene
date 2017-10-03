
#include "hen/io/File.h"

#include <Log.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

hen::io::File::File(const char* path)
	: File(std::string{ path })
{}
hen::io::File::File(const std::string& path)
	: m_path(path)
{
	auto start = m_path.find_last_of('/') + 1;
	auto end = m_path.find_last_of('.');
	m_name = m_path.substr(start, end - start);

	m_type = m_path.substr(m_path.find_last_of('.') + 1);
}

bool hen::io::File::exists() const
{
	struct stat fileInfo;
	return stat(m_path.c_str(), &fileInfo) == 0;
}
bool hen::io::File::create() const
{
	if (exists())
		return false;

	std::ofstream stream{ m_path };
	stream.close();
	return exists();
}
bool hen::io::File::erase() const
{
	return std::remove(getPath().c_str()) == 0;
}
std::string hen::io::File::read() const
{
	return std::string{
		std::istreambuf_iterator<char>(std::ifstream{ m_path }),
		std::istreambuf_iterator<char>()
	};
}
