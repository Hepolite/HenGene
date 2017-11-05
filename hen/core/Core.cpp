
#include "hen/core/Core.h"

#include "hen/asset/AssetHelper.h"
#include "hen/asset/AssetManager.h"
#include "hen/core/Allegro.h"
#include "hen/event/EventBus.h"
#include "hen/event/EventQueue.h"
#include "hen/logic/Loop.h"
#include "hen/logic/script/ScriptData.h"
#include "hen/logic/state/StateManager.h"
#include "hen/render/allegro/Font.h"
#include "hen/render/allegro/Sprite.h"
#include "hen/render/RenderCore.h"
#include "hen/render/shader/ShaderProgram.h"
#include "hen/render/uniform/UniformBlockManager.h"
#include "hen/ui/Display.h"
#include "hen/ui/gui/GuiManager.h"
#include "hen/ui/Keyboard.h"
#include "hen/ui/Mouse.h"

#include <Log.h>

#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include <glm/mat4x4.hpp>

class hen::Core::Internal
{
public:
	core::Allegro m_allegro;
	ui::Display m_display;
	render::RenderCore m_renderCore;
	uniform::UniformBlockManager m_uniformBlockManager;
	logic::Loop m_loop;
	event::EventBus m_eventBus;
	event::EventQueue m_eventQueue;
	ui::Keyboard m_keyboard;
	ui::Mouse m_mouse;
	asset::AssetManager m_assetManager;
	gui::GuiManager m_guiManager;
	state::StateManager m_stateManager;
};

hen::Core::Internal* hen::Core::m_internal = nullptr;

hen::Core::Core(const core::Settings& settings)
{
	LOG_INFO << "Setting up core resources...";
	m_internal = new Internal();

	LOG_INFO << "Creating display...";
	m_internal->m_display.create(settings.m_display.m_width, settings.m_display.m_height, settings.m_display.m_fullscreen);
	if (m_internal->m_display.getHandle() == nullptr)
		LOG_WARNING << "Failed to create display!";
	else
		LOG_INFO << "Display was successfully created!";

	LOG_INFO << "Setting up uniform blocks...";
	auto& cameraUBOBlock = m_internal->m_uniformBlockManager.create("Camera");
	cameraUBOBlock.addField<glm::mat4>("proj");
	cameraUBOBlock.addField<glm::mat4>("projInv");
	cameraUBOBlock.addField<glm::mat4>("view");
	cameraUBOBlock.addField<glm::mat4>("viewInv");
	cameraUBOBlock.addField<glm::mat4>("projview");
	cameraUBOBlock.addField<glm::mat4>("projviewInv");
	cameraUBOBlock.build();
	auto& modelUBOBlock = m_internal->m_uniformBlockManager.create("Model");
	modelUBOBlock.addField<glm::mat4>("transform");
	modelUBOBlock.build();
	LOG_INFO << "Done setting uniform blocks!";

	LOG_INFO << "Setting up main loop...";
	m_internal->m_loop.setProcessRate(settings.m_loop.m_cps);
	m_internal->m_loop.setFrameRate(settings.m_loop.m_fps);
	m_internal->m_loop.setLogic([this](float dt) { process(dt); });
	m_internal->m_loop.setRender([this](float dt) { render(dt); });
	if (m_internal->m_loop.start())
		LOG_INFO << "Successfully started main loop!";
	else
		LOG_WARNING << "Failed to start main loop!";

	LOG_INFO << "Registering event sources...";
	LOG_INFO << "Registering display event source...";
	m_internal->m_eventQueue.registerSource(al_get_display_event_source(m_internal->m_display.getHandle()));
	LOG_INFO << "Registering keyboard event source...";
	m_internal->m_eventQueue.registerSource(al_get_keyboard_event_source());
	m_internal->m_keyboard.initialize();
	LOG_INFO << "Registering mouse event source...";
	m_internal->m_eventQueue.registerSource(al_get_mouse_event_source());
	m_internal->m_mouse.initialize();
	LOG_INFO << "Event sources registered!";

	LOG_INFO << "Registering core assets...";
	hen::asset::AssetHelper helper;
	helper.add<hen::allegro::Font>("data/fonts", "xml", "data/fonts/");
	helper.add<hen::allegro::Sprite>("data/sprites", "xml", "data/sprites/");
	helper.add<hen::shader::ShaderProgram>("data/shaders", "xml", "data/shaders/");
	LOG_INFO << "Done registering core assets!";

	LOG_INFO << "Registering GUI logic...";
	m_internal->m_guiManager.initialize();
	LOG_INFO << "Done setting up GUI logic...";

	LOG_INFO << "Registering core scripting...";
	script::ScriptData data;
	data.setup();
	LOG_INFO << "Done setting up core scripting...";

	LOG_INFO << "Finished setting up core resources!";
}
hen::Core::~Core()
{
	delete m_internal;
}

hen::asset::AssetManager& hen::Core::getAssets()
{
	return m_internal->m_assetManager;
}
hen::event::EventQueue& hen::Core::getEventQueue()
{
	return m_internal->m_eventQueue;
}
hen::event::EventBus& hen::Core::getEventBus()
{
	return m_internal->m_eventBus;
}
hen::gui::GuiManager& hen::Core::getGuiManager()
{
	return m_internal->m_guiManager;
}
hen::logic::Loop& hen::Core::getMainLoop()
{
	return m_internal->m_loop;
}
hen::render::RenderCore& hen::Core::getRenderCore()
{
	return m_internal->m_renderCore;
}
hen::state::StateManager& hen::Core::getStateManager()
{
	return m_internal->m_stateManager;
}
hen::ui::Display& hen::Core::getDisplay()
{
	return m_internal->m_display;
}
hen::ui::Keyboard& hen::Core::getKeyboard()
{
	return m_internal->m_keyboard;
}
hen::ui::Mouse& hen::Core::getMouse()
{
	return m_internal->m_mouse;
}
hen::uniform::UniformBlockManager& hen::Core::getUniformBlockManager()
{
	return m_internal->m_uniformBlockManager;
}

void hen::Core::run()
{
	if (m_internal != nullptr)
		m_internal->m_loop.process();
}
void hen::Core::stop()
{
	if (m_internal != nullptr)
		m_internal->m_loop.stop();
}

void hen::Core::process(float dt)
{
	m_internal->m_keyboard.process();
	m_internal->m_mouse.process();
	m_internal->m_eventQueue.process();
	m_internal->m_guiManager.process(dt);
	m_internal->m_stateManager.process(dt);
	m_internal->m_renderCore.process(dt);
}
void hen::Core::render(float dt) const
{
	m_internal->m_renderCore.render(dt);
}
