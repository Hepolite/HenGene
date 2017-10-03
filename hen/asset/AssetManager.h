
#pragma once

#include "hen/asset/Node.h"
#include "hen/asset/Ref.h"
#include "hen/io/File.h"

#include <memory>
#include <string>
#include <typeinfo>
#include <unordered_map>

namespace hen
{
	namespace asset
	{
		class AssetManager
		{
		public:
			AssetManager() = default;
			AssetManager(const AssetManager&) = delete;
			AssetManager(AssetManager&&) = delete;
			~AssetManager() = default;

			AssetManager& operator=(const AssetManager&) = delete;
			AssetManager& operator=(AssetManager&&) = delete;

			template<class Asset, typename ...Args>
			void add(const std::string&name, const io::File& file, const Args& ...args)
			{
				auto& map = m_assets[typeid(Asset).hash_code()];
				map.emplace(name, std::make_unique<Node<Asset>>());
				auto node = static_cast<Node<Asset>*>(map[name].get());
				node->m_asset = std::make_unique<Asset>(args...);
				node->m_file = file;
			}
			template<class Asset>
			Ref<Asset> get(const std::string& name) const
			{
				const auto& search = m_assets.find(typeid(Asset).hash_code());
				if (search == m_assets.end())
					return Ref<Asset>{};
				const auto& map = search->second;
				const auto& result = map.find(name);
				if (result == map.end())
					return Ref<Asset>{};
				const auto& node = static_cast<Node<Asset>*>(result->second.get());
				return Ref<Asset>{ node };
			}

		private:
			using NodeCollection = std::unordered_map<std::string, std::unique_ptr<NodeBase>>;
			std::unordered_map<size_t, NodeCollection> m_assets;
		};
	}
}