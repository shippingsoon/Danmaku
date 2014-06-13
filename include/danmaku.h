#ifndef DANMAKU_H
#define DANMAKU_H

namespace stg
{
	class States;

	namespace Bgm
	{
		enum 
		{
			Intro = 1,
			Menu,
			Necro,
			Suwa,
			Moon,
			Curiosity,
			Wind,
			Nuclear,
			Ending
		};
	}
	
	namespace Sfx
	{
		enum 
		{
			Select = 0,
			Confirm,
			Cancel
		};
	}
	
	namespace Modes
	{
		enum
		{
			Easy, 
			Normal, 
			Hard,
			Lunatic
		};
	}
	
	class Danmaku
	{
		private:
			//A stack of game states.
			std::vector<States *> states;
		public:
			sf::RenderWindow window;
			sf::View camera;
			sf::RectangleShape screen;
			sf::Event event;
			sf::Font arial;
			sf::Text text;
			sf::Clock clock;
			sf::Time timer;
			std::vector<std::unique_ptr<sf::Music>> bgm;
			std::vector<sf::Sound> sfx;
			std::vector<sf::SoundBuffer> sfx_buffer;
			unsigned short int difficulty;
			bool is_focused, is_paused;
			sf::Color palette[MAX_BULLETS];
			void shufflePalette(sf::Vector2u r = {0, 0}, sf::Vector2u b = {0, 0}, sf::Vector2u g = {0, 0}, int a = 255);
			//Handle the events.
			void controller();
			//Handle events and game logic.
			void update();
			//Handles rendering routines.
			void render();
			//Push the state.
			void forward(States *state);
			//Pop the state.
			void rewind(bool stop = true);
			//Change the state.
			void transition(States *state);
			//Initialize the engine.
			Danmaku(int, int, std::string, int);
			//End all states and free up resources.
			~Danmaku();
	};
}

#endif

/* Copyleft 2013, Anonymous */
