
#pragma once

#include <memory>
#include <string>
#include <typeinfo>
#include <unordered_map>

namespace hen
{
	namespace gui
	{
		class ComponentData
		{
		public:
			template<typename T>
			void set(const std::string& key, const T& value)
			{
				const auto& hash = typeid(T).hash_code();
				const auto& result = m_data.find(hash);
				if (result == m_data.end())
					m_data.emplace(hash, std::make_unique<Data<T>>());
				static_cast<Data<T>*>(m_data[hash].get())->m_data[key] = value;
			}
			template<typename T>
			T get(const std::string& key, const T& def = T{ 0 }) const
			{
				const auto& result = m_data.find(typeid(T).hash_code());
				if (result == m_data.end())
					return def;
				const auto& data = static_cast<Data<T>*>(result->second.get());
				const auto& search = data->m_data.find(key);
				return search == data->m_data.end() ? def : search->second;
			}

		private:
			struct DataBase {};
			template<typename T> struct Data : DataBase { std::unordered_map<std::string, T> m_data; };

			std::unordered_map<size_t, std::unique_ptr<DataBase>> m_data;
		};
	}
}