#ifndef ENEMY_H
#define ENEMY_H
#include "main.h"
#include "path.h"


namespace stg
{
	class Enemy : public sf::CircleShape
	{
		private:
			
			sf::CircleShape bullet;
			float speed;
			int lives;
			Path route;
			friend class Stage;
			
		public:
			
			Enemy(sf::Vector2f origin = {0, 0}, float radius = 30, float speed = 20, sf::Color inner = sf::Color::Red, Trajectory path = Trajectory::None);
			void init(sf::Vector2f origin = {0, 0}, float radius = 30, float speed = 15, sf::Color inner = sf::Color::Red, Trajectory path = Trajectory::None);
			Enemy &setSpeed(float speed = 15);
			float getSpeed();
			Enemy &update();
			Enemy &debug(float speed);
	};
}



#endif

/* Copyleft 2013, Anonymous */
