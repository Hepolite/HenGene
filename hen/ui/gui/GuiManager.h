
#pragma once

namespace hen
{
	namespace gui
	{
		class GuiManager
		{
		public:
			GuiManager() = default;
			GuiManager(const GuiManager&) = delete;
			GuiManager(GuiManager&&) = delete;
			~GuiManager() = default;

			GuiManager& operator=(const GuiManager&) = delete;
			GuiManager& operator=(GuiManager&&) = delete;

		private:

		};
	}
}