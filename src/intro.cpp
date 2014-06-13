#include "../include/main.h"

namespace stg
{
	void Intro::start(Danmaku *game)
	{
		game->window.setTitle(CAPTION + std::string(" - Intro"));
		//Set the font's type, size and color.
		game->text.setString(LOGO);
		game->text.setFont(game->arial);
		game->text.setCharacterSize(30);
		game->text.setColor(sf::Color::Black);
		//Center the text.
		sf::FloatRect bounds = game->text.getLocalBounds();
		game->text.setOrigin(bounds.left + bounds.width / 2, bounds.top  + bounds.height / 2.0f);
		game->text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f));
		alpha = 0;
	}
	void Intro::controller(Danmaku *game)
	{
		//Check for all of the window's events.
		if (game->timer.asSeconds() > 0.5)
		{
			//If the ESCAPE key is pressed close the window.
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				game->window.close();
			//If any key is pressed skip the intro and transition into the start menu.
			if (game->event.type == sf::Event::KeyPressed)
				game->transition(Menu::instance());
		}
	}
	void Intro::update(Danmaku *game)
	{
		//The fade in effect is achieved by incrementing the alpha channel.
		if (alpha < 255)
		{
			alpha += 3;
			game->screen.setFillColor({255, 255, 255, alpha});
		}
		//Once the screen has faded, transition into the start menu state.
		else
			game->transition(Menu::instance());
	}
	void Intro::render(Danmaku *game)
	{
		game->window.draw(game->screen);
		game->window.draw(game->text);
	}
}

/* Copyleft 2013, Anonymous */
