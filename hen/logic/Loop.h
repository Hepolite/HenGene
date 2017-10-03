
#pragma once

#include <functional>

namespace hen
{
	namespace logic
	{
		class Loop
		{
		public:
			Loop() = default;
			Loop(const Loop&) = delete;
			Loop(Loop&&) = delete;
			~Loop() = default;

			Loop& operator=(const Loop&) = delete;
			Loop& operator=(Loop&&) = delete;

			void process();

			bool start();
			inline void stop() { m_isRunning = false; }
			inline bool isRunning() const { return m_isRunning; }

			inline void setLogic(const std::function<void(float)>& logic) { m_logic = logic; }
			inline void setRender(const std::function<void(float)>& render) { m_render = render; }
			inline void setProcessRate(double cps) { m_cps = cps; }
			inline void setFrameRate(double fps) { m_fps = fps; }

			inline double getProcessRate() const { return m_cps; }
			inline double getFrameRate() const { return m_cps; }

		private:
			std::function<void(float)> m_logic;
			std::function<void(float)> m_render;

			double m_cps = 0.0;
			double m_fps = 0.0;
			bool m_isRunning = false;
		};
	}
}