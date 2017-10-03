
#include "hen/logic/Loop.h"

#include <allegro5/allegro5.h>
#include <Log.h>

bool hen::logic::Loop::start()
{
	LOG(plog::info) << "Starting up main loop...";

	if (m_logic == nullptr || m_render == nullptr)
	{
		LOG(plog::fatal) << "Main loop has no logic and/or no rendering specified!";
		return false;
	}
	if (m_cps <= 0.0 || m_fps <= 0.0)
	{
		LOG(plog::fatal) << "Main loop cannot run with 0 cps and/or 0 fps";
		return false;
	}
	m_isRunning = true;
	LOG(plog::info) << "Main loop processing started!";
	return true;
}
void hen::logic::Loop::process()
{
	double accumulatedTime = 0.0;
	double currentTime = al_current_time();

	double t = 0.0;
	double dt = 1.0 / m_cps;

	while (m_isRunning)
	{
		double newTime = al_current_time();
		double frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulatedTime += frameTime;
		while (accumulatedTime > dt)
		{
			if (accumulatedTime < 1.0)
				m_logic(dt);
			else
			{
				double behindTime = accumulatedTime;
				double droppedFrames = std::floor(behindTime / dt);
				accumulatedTime -= droppedFrames * dt;
				LOG(plog::warning) << "Dropped " << droppedFrames << " updates; behind " << behindTime << "s";
			}
			accumulatedTime -= dt;
			t += dt;
		}
		m_render(accumulatedTime / dt);
	}
}