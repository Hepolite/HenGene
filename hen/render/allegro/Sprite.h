
#pragma once

#include "hen/io/File.h"

#include <allegro5/bitmap.h>
#include <allegro5/color.h>

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace hen
{
	namespace allegro
	{
		class Sprite
		{
		public:
			struct Frame
			{
				float m_x, m_y;
				float m_w, m_h;

				Frame() : Frame(0.0f, 0.0f, 0.0f, 0.0f) {}
				Frame(float x, float y, float w, float h) : m_x(x), m_y(y), m_w(w), m_h(h) {}
				~Frame() = default;
			};

			Sprite();
			Sprite(const Sprite&) = delete;
			Sprite(Sprite&&) = delete;
			~Sprite();

			Sprite& operator=(const Sprite&) = delete;
			Sprite& operator=(Sprite&&) = delete;

			void create(int width, int height);
			
			void onLoad(const io::File& file);
			void onUnload();

			unsigned int addFrame(float x, float y, float width, float height);
			unsigned int addFrameRow(float x, float y, float width, float height, float sep, int count);
			unsigned int addFrameCol(float x, float y, float width, float height, float sep, int count);
			unsigned int addFrameGrid(float x, float y, float width, float height, float sepX, float sepY, int countX, int countY);

			std::optional<Frame> getFrame(unsigned int index) const;
			std::optional<unsigned int> getFrameIndex(const std::string& name) const;
			inline unsigned int getFrameCount() const { return m_frames.size(); }
			inline ALLEGRO_BITMAP* getHandle() const { return m_handle; }

			void render(float x, float y, int flags = 0) const;
			void render(unsigned int frame, float x, float y, int flags = 0) const;
			void render(unsigned int frame, float x, float y, float angle, int flags = 0) const;
			void render(unsigned int frame, float x, float y, float width, float height, int flags = 0) const;
			void render(unsigned int frame, float x, float y, float width, float height, float angle, int flags = 0) const;

		private:
			ALLEGRO_BITMAP* m_handle = nullptr;
			ALLEGRO_COLOR m_tint{ 1.0f, 1.0f, 1.0f, 1.0f };

			std::vector<Frame> m_frames;
			std::unordered_map<std::string, unsigned int> m_frameNames;
		};
	}
}