#ifndef MODE_H
#define MODE_H
#include "../include/menu.h"

namespace stg
{
	class Mode : public Menu
	{
		private:
			static Mode mode;
		protected:
			Mode(){};
		public:
			void start(Danmaku *game);
			void play(Danmaku *game);
			void controller(Danmaku *game);
			static Mode *instance()
			{
				return &mode;
			}
	};
}

#endif

/* Copyleft 2013, Anonymous */
