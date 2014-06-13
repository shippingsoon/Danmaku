#include "../include/main.h"
#include "../include/common.h"

namespace stg
{
	void Stage::start(Danmaku *game)
	{
		//Set the window's title.
		game->window.setTitle(CAPTION + std::string(" - Stage 01"));
		game->bgm[Bgm::Necro]->setLoop(true);
		game->bgm[Bgm::Necro]->play();
		//
		game->shufflePalette({20, 200}, {50, 100}, {30, 230});
		//
		timeline = 0.f;
		//This will keep track of which paint layer we're currently on.
		layer_index = 0;
		//This 2 dimensional vector let's us manipulate the canvas sprite's position.
		canvas_position = {0, 0};
		//Attempt to load background textures.
		if (!background_texture.loadFromFile("data/img/bg/01.png") || !canvas_texture.loadFromFile("data/img/bg/canvas.png"))
			die("Error loading textures: data/img/bg/*.png", true, game);
		//Assign the textures to sprites.
		background_sprite.setTexture(background_texture);
		canvas_sprite.setTexture(canvas_texture);
		//Try to create a layer. This layer will act as a buffer for the two alternating paint layers.
		if (!buffer_layer.create(480, 560))
			die("Error creating renderTextures", 3, game);
		//Set the initial position of the sprites.
		buffer_sprite.setPosition(40, 20);
		paint_sprite[0].setPosition(0, 0);
		paint_sprite[1].setPosition(0, -560);
		for (int i = 0; i < 2; i++)
		{
			//Create the paint layers.
			if (!paint_layer[i].create(480, 560))
				die("Could not create paint layer", 3, game);
			paint_layer[i].clear({255, 255, 255, 0});
		}
		
		m_position[0] = {60, 0};
		m_position[1] = {60, 560};
		for (int i = 0; i < 2; i++)
		{
			m_circle[i].setRadius(30);
			m_circle[i].setPosition(m_position[i].x, m_position[i].y);
			m_circle[i].setFillColor(sf::Color::Green);
			m_circle[i].setOrigin(30, 30);
		}
		enemy[0].init({200, -40}, 30, 20, sf::Color::Red, Trajectory::Down);
		
		for (int i = 0; i < 20; i++)
		{
			bullet_position[i] = {300, 300};
			bullet[i].setRadius(30);
			bullet[i].setPosition(bullet_position[i].x, bullet_position[i].y);
			bullet[i].setFillColor(sf::Color::Blue);
			bullet[i].setOrigin(30, 30);
			bullet_radius[i] = bullet[i].getRadius();
			bullet_speed[i] = 0;
			bullet_angle[i] = 0;
		}
		game->is_focused = true;
	}
	void Stage::controller(Danmaku *game)
	{
		switch (game->event.type)
		{
			case sf::Event::KeyPressed:
				if (game->is_focused)
				{
					//If the ESCAPE key is pressed push the pause state on the stack.
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						//game->forward(Pause::instance());
						game->window.close();
					}
					
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
					{
						game->is_paused = true;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
					{
						game->is_paused = false;
					}
				}
				break;
		}
	}
	void Stage::update(Danmaku *game)
	{
		if (game->is_focused)
		{
			if (!game->is_paused)
			{
				timeline += (1.f/FPS);
			}
			
			switch ((int) timeline)
			{
				case 2:
					msg = "made it to 2";
					break;
				case 24:
					msg = "made it to 24";
					break;
				case 39:
					msg = "made it to 39";
					break;
			}
		}
		//Temporary debug function.
		tmp(game);
		
		for (int i = 0; i < 2; i++)
			m_position[i] = m_circle[i].getPosition();

		//If the first paint layer has moved off the screen, swap in the second paint layer.
		if (canvas_position.y == 560)
		{
			//Clear the current paint layer.
			paint_layer[layer_index].clear({255, 255, 255, 0});
			//Since this layer has moved off screen, move it above its replacement layer.
			paint_sprite[layer_index].setPosition(0, -560);
			m_circle[layer_index].setPosition(m_position[layer_index].x, ((560 + m_position[(layer_index == 0) ? 1 : 0].y)));
			//Invert the layer index.
			layer_index = (layer_index == 0) ? 1 : 0;
			//Reset the canvas' position to 0.
			canvas_position.y = 0;
		}
		
		//enemy[0].update();
	}
	void Stage::render(Danmaku *game)
	{
		//Draw the stage sprite to the screen.
		game->window.draw(background_sprite);
		
		canvas_sprite.setPosition(canvas_position.x, canvas_position.y);
		buffer_layer.draw(canvas_sprite);
		canvas_sprite.setPosition(canvas_position.x, canvas_position.y - 560);
		buffer_layer.draw(canvas_sprite);
		
		for (int i = 0; i < 2; i++)
		{
			paint_layer[i].draw(m_circle[i]);
			//Update the alternating paint layers.
			paint_layer[i].display();
			//Convert paint layers to sprites.
			paint_sprite[i].setTexture(paint_layer[i].getTexture());
			//Draw the alternating paint layers to the canvas layer.
			buffer_layer.draw(paint_sprite[i]);
		}
		
		//Update the buffer layer.
		buffer_layer.display();
		//Convert the buffer layer to a texture and assign said texture to a sprite.
		buffer_sprite.setTexture(buffer_layer.getTexture());
		game->window.draw(buffer_sprite);
		//game->window.draw(enemy[0]);
		
		//TEST AREA
		std::srand(std::time(NULL));
		static float angle = 2, speed = 10, degree = 180, duration = 0, offset = 90, hold = 0;
		static bool once = true;
		if (degree > 360)
			degree = 0;
		angle = math::degreeToRadian(degree);
		hold = 0;
		float max_bullets = 20,
			padding = 30,
			degrees = 45;
		for (int i = 0, a = (degrees - ((max_bullets * padding) / 2) + (padding / 2)) ; i < max_bullets; i++)
		{
			if (once)
			{
				bullet_color[i] = game->palette[i];
				bullet[i].setFillColor(bullet_color[i]);
				bullet_speed[i] = 0;
				bullet_angle[i] = 0;
			}
			bullet_speed[i] += 0.2;
			
			angle = math::degreeToRadian(a);
			bullet_angle[i] = angle;
			a += padding;
			
			bullet[i].setRadius(20);
			bullet_position[i].x += (bullet_speed[i] + offset) * std::cos(bullet_angle[i]);
			bullet_position[i].y += (bullet_speed[i] + offset) * std::sin(bullet_angle[i]);
			bullet[i].setPosition(bullet_position[i]);
			
			paint_layer[0].draw(bullet[i]);
			paint_layer[1].draw(bullet[i]);
			paint_layer[0].display();
			paint_layer[1].display();
		}
		once = false;
		offset = 0;
		
		//Debug
	}
	void Stage::stop(Danmaku *game)
	{
		
	}
	void Stage::play(Danmaku *game)
	{
		game->window.setTitle(CAPTION + std::string(" - Stage 01"));
	}
	void Stage::pause(Danmaku *game)
	{
	
	}
	void Stage::tmp(Danmaku *game)
	{
		int speed = 20;
		//Move the canvas layer.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			canvas_position.y += 10;
			for (int i = 0; i < 2; i++)
				paint_sprite[i].move(0, 10);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			canvas_position.y -= 10;
			for (int i = 0; i < 2; i++)
				paint_sprite[i].move(0, -10);
		}
		//Move the circle
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
		{
			for (int i = 0; i < 2; i++)
				m_circle[i].move(speed, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
		{
			for (int i = 0; i < 2; i++)
				m_circle[i].move(math::inverse(speed), 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
		{
			for (int i = 0; i < 2; i++)
				m_circle[i].move(0, speed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
		{
			for (int i = 0; i < 2; i++)
				m_circle[i].move(0, math::inverse(speed));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			game->window.close();
		}
		
	}
}

/* Copyleft 2013, Anonymous */
