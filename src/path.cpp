#include "../include/main.h"

namespace stg
{
	//Set the initial point and optionally choose a predefined path.
	Path::Path(sf::Vector2f origin, Trajectory path, Enemy *enemy)
	{
		this->enemy = enemy;
		_setPath(origin, path);
	}
	//Add a point to the path.
	Path &Path::setPoint(sf::Vector2f point)
	{
		points.push_back(point);
		return *this;
	}
	//Gets the vector of points. These points will be used to plot a path.
	std::vector<sf::Vector2f> Path::getPoint()
	{
		return points;
	}
	//Set an initial path.
	Path &Path::_setPath(sf::Vector2f origin, Trajectory path, float offset, int n)
	{
		//Add the initial point.
		setPoint(origin);
		//If we have a predefined path.
		if (path > Trajectory::None)
		{
			for (int i = 0; i < n; i++)
			{
				switch (path)
				{
					//Only increment the y-axis relative to origin. This will send us south.
					case Trajectory::Down:
						origin.y += offset;
						break;
					//Only increment the x-axis. This will send us east.
					case Trajectory::Right:
						origin.x += offset;
						break;
					//Only decrement the x-axis. This will send us west.
					case Trajectory::Left:
						origin.x -= offset;
						break;
				}
				setPoint({origin.x, origin.y});
			}
		}
		//Set the current iterator to the beginning.
		current = std::begin(points);
		return *this;
	}
	//Change an existing path.
	Path &Path::setPath(sf::Vector2f origin, Trajectory path, float offset, int n)
	{
		points.clear();
		_setPath(origin, path, offset, n);
		return *this;
	}
	//Advance the enemy's position by making it plot the points of a vector.
	Path &Path::followPath(float radius)
	{
		std::vector<sf::Vector2f>::iterator target;
		sf::Vector2f position;
		float angle, distance, speed;
		//Make sure we are not at the end of the points vector.
		if (current != points.end() - 1)
		{
			std::cout << std::to_string(current - points.begin()) + "\n";
			//std::cout << std::to_string(points.size() - 1) + "\n";
			//Get the enemy's speed.
			speed = enemy->getSpeed();
			//The target iterator will point to the next element in the vector.
			target = std::next(current);
			//Get the enemy's position.
			position = enemy->getPosition();
			//The distance between the enemy and target.
			distance = math::distance(position, *target);
			//If the distance between the enemy and the target is smaller than the target's radius, advance our position.
			if (distance < radius)
				current++;
			//Adjust the enemy's speed if it is moving at a rate that would skip over the target.
			if ((distance + radius) < (speed * 2))
				speed = distance;
			//Get the angle that the enemy needs to travel in to reach the target.
			angle = math::getTargetAngle(*target, position);
			//Convert our polar coordinates to cartesian coordinates.
			position.x += speed * std::cos(angle);
			position.y += speed * std::sin(angle);
			//Advance the enemy's position to reach the target.
			enemy->setPosition(position.x, position.y);
		}
		return *this;
	}
	//Alter which enemy we are pointing to.
	Path &Path::setEnemy(Enemy *enemy)
	{
		this->enemy = enemy;
		return *this;
	}
	
	
}


/* Copyleft 2013, Anonymous */
