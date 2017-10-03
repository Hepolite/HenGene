
#include "hen/render/RenderCore.h"

#include "hen/render/opengl/OpenGL.h"

#include <allegro5/display.h>

#undef OPAQUE
#undef TRANSPARENT

hen::render::RenderCore::RenderCore()
{
}
hen::render::RenderCore::~RenderCore()
{
}

hen::render::Renderer hen::render::RenderCore::addRenderer(RenderLayer layer, std::function<const void(float)>&& render)
{
	const auto index = m_uniqueRendererIndex++;
	m_renderers[layer][index] = render;
	return Renderer{ layer, index };
}
void hen::render::RenderCore::deleteRenderer(const Renderer& renderer)
{
	m_renderers[renderer.m_layer].erase(renderer.m_index);
}

void hen::render::RenderCore::initialize2DRendering() const
{
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
}
void hen::render::RenderCore::initialize3DRendering() const
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void hen::render::RenderCore::process(float dt)
{
	for (auto& camera : m_cameras)
		camera.second.process();
}
void hen::render::RenderCore::render(float dt) const
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	initialize3DRendering();
	render3D(dt);
	initialize2DRendering();
	render2D(dt);

	al_flip_display();
}
void hen::render::RenderCore::renderLayer(RenderLayer layer, float dt) const
{
	const auto& map = m_renderers.find(layer);
	if (map == m_renderers.end())
		return;

	for (const auto& renderer : map->second)
		renderer.second(dt);
}
void hen::render::RenderCore::render2D(float dt) const
{
	renderLayer(RenderLayer::SCREEN, dt);
}
void hen::render::RenderCore::render3D(float dt) const
{
	for (const auto& camera : m_cameras)
	{
		camera.second.upload(dt);
		// TODO: Bind/unbind FBO if neccessary
		renderLayer(RenderLayer::OPAQUE, dt);
		renderLayer(RenderLayer::CUTOUT, dt);
		renderLayer(RenderLayer::TRANSPARENT, dt);
	}
}

