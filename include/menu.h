#ifndef MENU_H
#define MENU_H

namespace stg
{
	class Menu : public States
	{
		private:
			static Menu menu;
		protected:
			std::vector<std::string> menu_map;
			sf::FloatRect bounds;
			int menu_index, menu_spacing;
			Menu(){};
		public:
			void start(Danmaku *game);
			void stop(Danmaku *game);
			void play(Danmaku *game);
			void pause(Danmaku *game){};
			void controller(Danmaku *game);
			void update(Danmaku *game){};
			void render(Danmaku *game);
			static Menu *instance()
			{
				return &menu;
			}
	};
}

#endif

/* Copyleft 2013, Anonymous */
