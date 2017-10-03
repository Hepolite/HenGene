
#pragma once

#include "hen/asset/Node.h"

#include <memory>

namespace hen
{
	namespace asset
	{
		template<class Asset>
		class Ref
		{
		public:
			Ref() = default;
			Ref(std::unique_ptr<Asset>&& data) : m_data(std::move(data)) {}
			Ref(Node<Asset>* handle)
				: m_handle(handle)
			{
				if (m_handle != nullptr)
				{
					if (m_handle->m_refs == 0 && m_handle->m_asset != nullptr)
						m_handle->m_asset->onLoad(m_handle->m_file);
					handle->m_refs++;
				}
			}
			Ref(const Ref& other) = delete;
			Ref(Ref&& other)
			{
				m_handle = other.m_handle;
				m_data = std::move(other.m_data);
				other.m_handle = nullptr;
				other.m_data = nullptr;
			}
			~Ref()
			{
				if (m_handle != nullptr)
				{
					m_handle->m_refs--;
					if (m_handle->m_refs == 0 && m_handle->m_asset != nullptr)
						m_handle->m_asset->onUnload();
				}
			}

			Ref& operator=(const Ref&) = delete;
			Ref& operator=(Ref&& other)
			{
				m_handle = other.m_handle;
				m_data = std::move(other.m_data);
				other.m_handle = nullptr;
				other.m_data = nullptr;
				return *this;
			}
			inline bool operator==(const std::nullptr_t&) const { return (m_handle == nullptr || m_handle->m_asset == nullptr) && m_data == nullptr; }
			inline bool operator!=(const std::nullptr_t&) const { return (m_handle != nullptr && m_handle->m_asset != nullptr) || m_data != nullptr; }
			inline const Asset* operator->() const { return m_data == nullptr ? m_handle->m_asset.get() : m_data.get(); }

		private:
			Node<Asset>* m_handle = nullptr;
			std::unique_ptr<Asset> m_data = nullptr;
		};
	}
}