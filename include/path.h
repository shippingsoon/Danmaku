#ifndef PATH_H
#define PATH_H
#include "enemy.h"

namespace stg
{
	class Enemy;
	
	enum class Trajectory : unsigned int
	{
		None = 0,
		Down,
		Right,
		Left
	};
	
	class Path
	{
		private:
			std::vector<sf::Vector2f> points;
			std::vector<sf::Vector2f>::iterator current;
			Path &_setPath(sf::Vector2f origin = {0, 0}, Trajectory path = Trajectory::None, float offset = 50, int n = 10);
			Enemy *enemy;
		public:
			std::vector<sf::Vector2f> getPoint();
			Path(sf::Vector2f origin = {0, 0}, Trajectory path = Trajectory::None, Enemy *enemy = NULL);
			Path &setPoint(sf::Vector2f point);
			Path &followPath(float radius = 10);
			Path &setPath(sf::Vector2f origin = {0, 0}, Trajectory path = Trajectory::None, float offset = 50, int n = 10);
			Path &setEnemy(Enemy *enemy);
	};
}

#endif

/* Copyleft 2013, Anonymous */
