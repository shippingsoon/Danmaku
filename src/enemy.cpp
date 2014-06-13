#include "../include/main.h"
#include "../include/path.h"

namespace stg
{
	Enemy::Enemy(sf::Vector2f origin, float radius, float speed, sf::Color inner, Trajectory path) : route(origin, path, this)
	{
		init(origin, radius, speed, inner, path);
	}
	void Enemy::init(sf::Vector2f origin, float radius, float speed, sf::Color inner, Trajectory path)
	{
		setRadius(radius);
		setPosition(origin.x, origin.y);
		setFillColor(inner);
		setOutlineColor(sf::Color::Black);
		setOutlineThickness(2);
		setOrigin(radius, radius);
		setSpeed(speed);
		route.setPath(origin, path);
	}
	Enemy &Enemy::setSpeed(float speed)
	{
		this->speed = speed;
		return *this;
	}
	float Enemy::getSpeed()
	{
		return speed;
	}
	Enemy &Enemy::update()
	{
		route.followPath(10);
		debug(20);
	}
	Enemy &Enemy::debug(float speed)
	{
		//Move the enemy.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) 
			move(speed, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) 
			move(math::inverse(speed), 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) 
			move(0, speed);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) 
			move(0, math::inverse(speed));
	}
}

/* Copyleft 2013, Anonymous */
