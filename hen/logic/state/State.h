
#pragma once

namespace hen
{
	namespace state
	{
		class State
		{
		public:
			State() = default;
			virtual ~State() = default;

			virtual void onInitialize() = 0;
			virtual void onDeinitialize() = 0;
			virtual void onProcess(float dt) = 0;

			inline void setPaused(bool paused) { m_isPaused = paused; }
			inline bool isPaused() const { return m_isPaused; }

		private:
			bool m_isPaused = false;
		};
	}
}