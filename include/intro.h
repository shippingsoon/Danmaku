#ifndef INTRO_H
#define INTRO_H

namespace stg
{
	class Intro: public States
	{
		private:
			sf::Uint8 alpha;
			static Intro intro;
		protected:
			Intro(){};
		public:
			void start(Danmaku *game);
			void stop(Danmaku *game){};
			void play(Danmaku *game){};
			void pause(Danmaku *game){};
			void controller(Danmaku *game);
			void update(Danmaku *game);
			void render(Danmaku *game);
			static Intro *instance()
			{
				return &intro;
			}
	};
}

#endif

/* Copyleft 2013, Anonymous */
