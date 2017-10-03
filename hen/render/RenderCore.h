
#pragma once

#include "hen/render/Camera.h"
#include "hen/render/opengl/FBO.h"
#include "hen/render/Renderer.h"
#include "hen/render/RenderLayer.h"

#include <map>
#include <unordered_map>

namespace hen
{
	namespace render
	{
		class RenderCore
		{
		public:
			RenderCore();
			RenderCore(const RenderCore&) = delete;
			RenderCore(RenderCore&&) = delete;
			~RenderCore();

			RenderCore& operator=(const RenderCore&) = delete;
			RenderCore& operator=(RenderCore&&) = delete;

			void process(float dt);
			void render(float dt) const;

			Renderer addRenderer(RenderLayer layer, std::function<const void(float)>&& render);
			void deleteRenderer(const Renderer& renderer);

			inline Camera& getMainCamera() { return getCamera(0); }
			inline Camera& getCamera(unsigned int index) { return m_cameras[index]; }
			inline void deleteCamera(unsigned int index) { m_cameras.erase(index); }
			inline opengl::FBO& getFBO(unsigned int index) { return m_fbos[index]; }
			inline void deleteFBO(unsigned int index) { m_fbos.erase(index); }

		private:
			void initialize2DRendering() const;
			void initialize3DRendering() const;

			void renderLayer(RenderLayer layer, float dt) const;
			void render2D(float dt) const;
			void render3D(float dt) const;

			std::map<unsigned int, Camera> m_cameras;
			std::unordered_map<unsigned int, opengl::FBO> m_fbos;
			std::unordered_map<RenderLayer, std::unordered_map<unsigned int, std::function<const void(float)>>> m_renderers;

			unsigned int m_uniqueRendererIndex = 0;
		};
	}
}