#include "../include/main.h"

namespace stg
{
	Danmaku::Danmaku(int w, int h, std::string caption, int fps):
	window(sf::VideoMode(w, h), caption),
	camera(sf::Vector2f(w/2, h/2), sf::Vector2f(800, 600))
	{
		//Synchronize the game's refresh rate with the vertical frequency of the monitor.
		window.setVerticalSyncEnabled(true);
		//Limit the framerate to n frames per second.
		window.setFramerateLimit(fps);
		//Reset the clock.
		clock.restart();
		//Attempt to load a font.
		if (!arial.loadFromFile("data/font/arial.ttf"))
			die("Error loading font: data/font/arial.ttf", 2, this);
		//Set the screen's size and color.
		screen.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
		screen.setFillColor(sf::Color::Black);
		//Set the font's type, size and color.
		text.setFont(arial);
		text.setCharacterSize(28);
		text.setColor(sf::Color::White);
		//An associative array of background music which will be used to load files.
		std::map<std::string, int> bgm_map = {
			{"intro.ogg", Bgm::Intro},
			{"menu.ogg", Bgm::Menu},
			{"stage-01a.ogg", Bgm::Necro},
			{"stage-01a.ogg", Bgm::Suwa},
			{"stage-01b.ogg", Bgm::Moon},
			{"stage-02b.ogg", Bgm::Curiosity},
			{"stage-01c.ogg", Bgm::Wind},
			{"stage-02c.ogg", Bgm::Nuclear},
			{"ending.ogg", Bgm::Ending}
		};
		//Iterate through the map and load the bgm.
		for (std::map<std::string, int>::iterator i = bgm_map.begin(); i != bgm_map.end(); ++i)
		{
			//Try to load some sounds.
			std::unique_ptr<sf::Music> tmp(new sf::Music());
			std::string filepath = "data/bgm/" + (*i).first;
			if (!tmp->openFromFile(filepath))
				die("Error loading bgm:" + filepath, 2, this);
			bgm.push_back(std::move(tmp));
		}
		//An associative array of sound effects which will be used to load files.
		std::map<std::string, int> sfx_map = {
			{"select.ogg", Sfx::Select},
			{"confirm.ogg", Sfx::Confirm},
			{"cancel.ogg", Sfx::Cancel}
		};
		//Resize the sfx.
		sfx_buffer.resize(sfx_map.size());
		sfx.resize(sfx_map.size());
		//Iterate through the map and load the sfx.
		for (std::map<std::string, int>::iterator i = sfx_map.begin(); i != sfx_map.end(); ++i)
		{
			//Try to load some sounds.
			std::string filepath = "data/sfx/" + (*i).first;
			if (!sfx_buffer[(*i).second].loadFromFile(filepath))
				die("Error loading sfx: data/sfx/" + filepath, 3, this);
			sfx[(*i).second].setBuffer(sfx_buffer[(*i).second]);
		}
		is_paused = false;
	}
	Danmaku::~Danmaku()
	{
		//Loop through all states and call their deconstructors.
		while (!states.empty())
		{
			states.back()->stop(this);
			states.pop_back();
		}
	}
	void Danmaku::controller()
	{
		timer = clock.getElapsedTime();
		//Handle common events.
		if (window.pollEvent(event))
		{
			switch (event.type)
			{
				//Exit if the user closes the window.
				case sf::Event::Closed:
					window.close();
					break;
				//If the window has gained focus.
				case sf::Event::GainedFocus:
					is_focused = true;
					break;
				//If the window has lost focus.
				case sf::Event::LostFocus:
					is_focused = false;
					break;
			}
			//Handle this state's events.
			states.back()->controller(this);
		}
	}
	void Danmaku::update()
	{
		//Handle events and game logic.
		states.back()->update(this);
	}
	void Danmaku::render()
	{
		//Set the view.
		window.setView(camera);
		//Clear the window.
		window.clear(sf::Color::Black);
		//Render the current state.
		states.back()->render(this);
		window.display();
	}
	void Danmaku::forward(States *state)
	{
		//Pause the current state.
		if (!states.empty())
			states.back()->pause(this);
		//Push a new state.
		states.push_back(state);
		states.back()->start(this);
	}
	void Danmaku::rewind(bool stop)
	{
		//Pop the current state.
		if (!states.empty())
		{
			if (stop)
				states.back()->stop(this);
			states.pop_back();
		}
		//Resume the previous state.
		if (!states.empty())
			states.back()->play(this);
	}
	void Danmaku::transition(States *state)
	{
		if (!states.empty())
		{
			//Stop the current state.
			states.back()->stop(this);
			states.pop_back();
		}
		//Transition into a new state by pushing a new state onto the stack.
		clock.restart();
		states.push_back(state);
		states.back()->start(this);
	}
	void Danmaku::shufflePalette(sf::Vector2u r, sf::Vector2u b, sf::Vector2u g, int a)
	{
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			palette[i].r = (std::rand() % r.y) + r.x;
			palette[i].g = (std::rand() % g.y) + g.x;
			palette[i].b = (std::rand() % b.y) + b.x;
			palette[i].a = a;
		}
	}
	
}

/* Copyleft 2013, Anonymous */
