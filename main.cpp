#include "main.h"
stg::Intro stg::Intro::intro;
stg::Mode stg::Mode::mode;
stg::Menu stg::Menu::menu;
stg::Stage stg::Stage::stage;
stg::Player stg::Player::player;

int main(void)
{
	//Initialize the game's resources.
	stg::Danmaku game(WINDOW_WIDTH, WINDOW_HEIGHT, CAPTION, FPS);
	//Transition into the intro state.
	game.transition(stg::Stage::instance());
	//Keep the app running until the window is closed.
	while (game.window.isOpen())
	{
		game.controller();
		game.update();
		game.render();
	}
	return EXIT_SUCCESS;
}

/* Copyleft 2013, Anonymous */