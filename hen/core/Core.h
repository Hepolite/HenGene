
#pragma once

#include "hen/core/Settings.h"

namespace hen
{
	namespace asset { class AssetManager; }
	namespace event { class EventBus; }
	namespace event { class EventQueue; }
	namespace gui { class GuiManager; }
	namespace logic { class Loop; }
	namespace render { class RenderCore; }
	namespace state { class StateManager; }
	namespace ui { class Display; }
	namespace ui { class Keyboard; }
	namespace ui { class Mouse; }
	namespace uniform { class UniformBlockManager; }

	class Core
	{
	public:
		Core(const core::Settings& settings);
		~Core();

		static asset::AssetManager& getAssets();
		static event::EventBus& getEventBus();
		static event::EventQueue& getEventQueue();
		static gui::GuiManager& getGuiManager();
		static const logic::Loop& getMainLoop();
		static render::RenderCore& getRenderCore();
		static state::StateManager& getStateManager();
		static ui::Display& getDisplay();
		static const ui::Keyboard& getKeyboard();
		static const ui::Mouse& getMouse();
		static uniform::UniformBlockManager& getUniformBlockManager();

		void run();
		static void stop();

	private:
		void process(float dt);
		void render(float dt) const;

		class Internal;
		static Internal* m_internal;
	};
}