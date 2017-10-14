
#pragma once

#include <allegro5/keycodes.h>

namespace hen
{
	namespace events
	{
		class KeyPress
		{
		public:
			KeyPress(int key, unsigned int modifiers)
				: m_key(key), m_modifiers(modifiers)
			{}
			~KeyPress() = default;

			inline int getKey() const { return m_key; }
			inline unsigned int getModifiers() const { return m_modifiers; }

		private:
			int m_key;
			unsigned int m_modifiers;
		};

		class KeyRelease
		{
		public:
			KeyRelease(int key, unsigned int modifiers)
				: m_key(key), m_modifiers(modifiers)
			{}
			~KeyRelease() = default;

			inline int getKey() const { return m_key; }
			unsigned inline int getModifiers() const { return m_modifiers; }

		private:
			int m_key;
			unsigned int m_modifiers;
		};

		class KeyUnichar
		{
		public:
			KeyUnichar(int unichar, unsigned int modifiers)
				: m_unichar(unichar), m_modifiers(modifiers)
			{}
			~KeyUnichar() = default;

			inline int getUnichar() const { return m_unichar; }
			inline unsigned int getModifiers() const { return m_modifiers; }

		private:
			int m_unichar;
			unsigned int m_modifiers;
		};
	}
}