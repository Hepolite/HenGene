
#pragma once

#include "hen/core/Core.h"
#include "hen/asset/AssetManager.h"

#include "hen/io/File.h"
#include "hen/io/Folder.h"

#include <string>

namespace hen
{
	namespace asset
	{
		class AssetHelper
		{
		public:
			template<typename T, typename ...Args>
			void add(
				const io::Folder& folder,
				const std::string& extension = "xml",
				const std::string& ignore = "data/",
				const Args& ...args
			)
			{
				for (const auto& file : folder.getFiles())
				{
					if (file.getType() == extension)
					{
						const auto first = ignore.length();
						const auto last = file.getPath().find_last_of('.');
						const std::string name = file.getPath().substr(first, last - first);
						Core::getAssets().add<T, Args...>(name, file, args...);
					}
				}
				for (const auto& subFolder : folder.getFolders())
					add<T, Args...>(subFolder, extension, ignore, args...);
			}
		};
	}
}