#include "../include/main.h"

namespace stg
{
	void Mode::start(Danmaku *game)
	{
		//Set the window's caption.
		game->window.setTitle(CAPTION + std::string(" - Mode Menu"));
		//Keep track of which menu we're currently on.
		menu_index = 0;
		menu_spacing = 50;
		//A list of menu items.
		menu_map = {
			{"Easy"},
			{"Normal"},
			{"Hard"},
			{"Lunatic"},
			{"Return"}
		};
	}
	void Mode::controller(Danmaku *game)
	{
		//Check for all of the window's events.
		if (game->timer.asSeconds() > 0.5)
		{
			switch (game->event.type)
			{
				case sf::Event::KeyPressed:
					if (game->is_focused)
					{
						//If the X or ESCAPE key is pressed return to the previous menu.
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						{
							game->sfx[Sfx::Cancel].play();
							if (menu_index == menu_map.size() - 1)
								game->rewind(false);
							else 
								menu_index = (menu_map.size() - 1);
						}
						//If the Z or RETURN key is pressed.
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
						{
							game->sfx[Sfx::Confirm].play();
							switch (menu_index)
							{
								//The user selected easy mode.
								case Modes::Easy:
									game->difficulty = Modes::Easy;
									break;
								//The user selected normal mode.
								case Modes::Normal:
									game->difficulty = Modes::Normal;
									break;
								//The user selected hard mode.
								case Modes::Hard:
									game->difficulty = Modes::Hard;
									break;
								//The user selected lunatic mode.
								case Modes::Lunatic:
									game->difficulty = Modes::Lunatic;
									break;
								//The user selected return.
								default:
									game->sfx[Sfx::Cancel].play();
									game->rewind(false);
							}
							if (menu_index <= Modes::Lunatic)
								game->transition(Stage::instance());
						}
						//If the DOWN key is pressed increment the menu's index.
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							game->sfx[Sfx::Select].play();
							menu_index = (menu_index < (menu_map.size() - 1)) ? menu_index + 1 : 0;
						}
						//If the UP key is pressed decrement the menu's index.
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						{
							game->sfx[Sfx::Select].play();
							menu_index = (menu_index > 0) ? menu_index - 1 : (menu_map.size() - 1);
						}
					}
					break;
			}
		}
	}
	void Mode::play(Danmaku *game)
	{
		//Set the window's title.
		game->window.setTitle(CAPTION + std::string(" - Mode Menu"));
	}
}

/* Copyleft 2013, Anonymous */
