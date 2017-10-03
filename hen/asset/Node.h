
#pragma once

#include "hen/io/File.h"

#include <memory>

namespace hen
{
	namespace asset
	{
		struct NodeBase {};

		template<class Asset>
		struct Node : public NodeBase
		{
			std::unique_ptr<Asset> m_asset;
			io::File m_file{ "" };
			unsigned int m_refs = 0;
		};
	}
}