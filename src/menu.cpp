#include "../include/main.h"

namespace stg
{
	void Menu::start(Danmaku *game)
	{
		//Set the window's caption.
		game->window.setTitle(CAPTION + std::string(" - Start Menu"));
		//Set the font's type and size.
		game->text.setFont(game->arial);
		game->text.setCharacterSize(40);
		//Keeps track of which menu we're currently on.
		menu_index = 0;
		menu_spacing = 50;
		//A list of menu items.
		menu_map = {
			{"Start"},
			{"Extra"},
			{"Config"},
			{"Quit"}
		};
		//Play and loop the title music.
		game->bgm[Bgm::Menu]->setLoop(true);
		game->bgm[Bgm::Menu]->play();
	}
	void Menu::controller(Danmaku *game)
	{
		//Check for all of the window's events.
		if (game->timer.asSeconds() > 0.5)
		{
			switch (game->event.type)
			{
				case sf::Event::KeyPressed:
					if (game->is_focused)
					{
						//If the ESCAPE key is pressed close the window.
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						{
							game->window.close();
						}
						//If the X key is pressed set the menu's index to quit.
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
						{
							game->sfx[Sfx::Cancel].play();
							if (menu_index == (menu_map.size() -1))
								game->window.close();
							else
								menu_index = (menu_map.size() -1);
						}
						//If the Z or RETURN key is pressed.
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
						{
							//Play a game sfx.
							game->sfx[Sfx::Confirm].play();
							switch (menu_index)
							{
								//The user selected Start.
								case 0:
									game->forward(Mode::instance());
									break;
								//The user selected Quit.
								case 3:
									game->window.close();
									break;
							}
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
	void Menu::render(Danmaku *game)
	{
		//Clear the screen
		game->window.clear(sf::Color::White);
		//Draw the menu's options.
		for (int i = 0; i < menu_map.size(); i++)
		{
			game->text.setString(menu_map[i]);
			//Highlight a menu if its index has been selected.
			(menu_index == i)
				? game->text.setColor(sf::Color::Red)
				: game->text.setColor(sf::Color::Black);
			//Make the menu's text centered.
			bounds = game->text.getLocalBounds();
			game->text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top  + bounds.height / 2.0f);
			game->text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, 200 + (menu_spacing * i)));
			//Draw the menu's text.
			game->window.draw(game->text);
			
		}
	}
	void Menu::stop(Danmaku *game)
	{
		//Stop the music.
		game->bgm[Bgm::Menu]->stop();
	}
	void Menu::play(Danmaku *game)
	{
		//Set the window's title.
		game->window.setTitle(CAPTION + std::string(" - Start Menu"));
	}
}

/* Copyleft 2013, Anonymous */
