#ifndef PLAYER_H
#define PLAYER_H
#include "danmaku.h"

namespace stg
{
	class Player : public sf::CircleShape
	{
		private:
			sf::CircleShape bullet;
			sf::Color primary, secondary;
			bool focused;
			Danmaku *game;
			sf::CircleShape &getBullet()
			{
				return bullet;
			}
			void setBulletPosition(int x = 0, int y = 0)
			{
				bullet.setPosition(x, y);
			}
			sf::Vector2f getBulletPosition(int x = 0, int y = 0)
			{
				return bullet.getPosition();
			}
			int inverse(int n)
			{
				n -= n * 2;
				return n;
			}
			static Player player;
			friend class Stage;
		protected:
			Player(){};
		public:
			unsigned int r, health, speed, lives, acceleration;
			static Player *instance()
			{
				return &player;
			}
			void init(Danmaku *game, int x = 0, int y = 0, int r = 10, sf::Color p = sf::Color::Blue, sf::Color s = sf::Color::Green)
			{
				this->game = game;
				setRadius(r);
				acceleration = 16;
				lives = 4;
				primary = p;
				secondary = s;
				setPosition(x, y);
				setOutlineColor(primary);
				setOutlineThickness(5);
				setOrigin(r, r);
				bullet.setRadius(30);
				bullet.setOrigin(30, 30);
				bullet.setFillColor(sf::Color::Green);
				
			}
			void update()
			{
				//If the SHIFT key is pressed switch to focused mode.
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)))
				{
					speed = acceleration / 2;
					focused = true;
				}
				else
				{
					speed = acceleration;
					focused = false;
				}
				setOutlineColor((focused) ? secondary : primary);
				//If the RIGHT key is pressed.
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					move(speed, 0);
				}
				//If the LEFT key is pressed.
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					move(inverse(speed), 0);
				}
				//If the DOWN key is pressed.
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					move(0, speed);
				}
				//If the UP key is pressed.
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					move(0, inverse(speed));
				}
			}
			void update_bullet(int y = 0)
			{
				speed = acceleration;
				//sf::Vector2f tmp = bullet.getPosition();
				//bullet.setPosition(tmp.x, tmp.y + y);
				//If the RIGHT key is pressed.
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					bullet.move(speed, 0);
				}
				//If the LEFT key is pressed.
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					bullet.move(inverse(speed), 0);
				}
				//If the DOWN key is pressed.
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					bullet.move(0, speed);
				}
				//If the UP key is pressed.
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
				
					bullet.move(0, inverse(speed));
				}
				
			}
	};
}

#endif

/* Copyleft 2013, Anonymous */
