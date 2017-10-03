
#pragma once

#include "hen/render/uniform/UBO.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace hen
{
	namespace uniform
	{
		class UniformBlockManager
		{
		public:
			UBO& create(const std::string& name);
			bool has(const std::string& name) const;
			const UBO& get(const std::string& name) const;

			inline const std::unordered_map<std::string, unsigned int>& getBindings() const { return m_ports; }

		private:
			std::unordered_map<std::string, UBO> m_ubos;
			std::unordered_map<std::string, unsigned int> m_ports;
			unsigned int m_nextPortIndex = 1;
		};
	}
}