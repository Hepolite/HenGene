
#include <sys/stat.h>

#include "hen/io/Folder.h"

#include <dirent.h>

hen::io::Folder::Folder(const char* path)
	: Folder(std::string{ path })
{}
hen::io::Folder::Folder(const std::string& path)
	: m_path(path)
{
	m_name = m_path.substr(m_path.find_last_of('/') + 1);
}

bool hen::io::Folder::exists() const
{
	struct stat dirInfo;
	return stat(m_path.c_str(), &dirInfo) == 0 && (dirInfo.st_mode & S_IFDIR) != 0;
}

template<class T>
std::vector<T> getEntry(const std::string& path, int filter)
{
	DIR* dir = opendir(path.c_str());
	if (dir == nullptr)
		return{};
	struct stat st;

	std::vector<T> entries;
	for (struct dirent* ent; (ent = readdir(dir)) != nullptr; )
	{
		const std::string file_name = ent->d_name;
		const std::string full_file_name = path + "/" + file_name;

		if (file_name[0] == '.')
			continue;
		if (stat(full_file_name.c_str(), &st) == -1)
			continue;

		if ((st.st_mode & filter) != 0)
			entries.emplace_back(full_file_name);
	}
	return entries;
}
std::vector<hen::io::Folder> hen::io::Folder::getFolders() const
{
	return getEntry<Folder>(m_path, S_IFDIR);
}
std::vector<hen::io::File> hen::io::Folder::getFiles() const
{
	return getEntry<File>(m_path, S_IFMT & ~S_IFDIR);
}
