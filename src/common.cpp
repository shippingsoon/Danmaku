#include "../include/main.h"

namespace stg
{
	namespace math
	{
		//Returns the distance between two points.
		float distance(float ax, float ay, float bx, float by)
		{
			return std::sqrt(std::pow(bx - ax, 2) + std::pow(by - ay, 2)); 
		}
		//Overload the distance function with a different number of parameters.
		float distance(sf::Vector2f a, sf::Vector2f b)
		{
			return distance(a.x, a.y, b.x, b.y);
		}
		//Get the angle of a target.
		float getTargetAngle(float target_x, float target_y, float x, float y)
		{
			return std::atan2(target_y - y, target_x - x);
		}
		//Overload the getTargetAngle function with a different number of parameters.
		float getTargetAngle(sf::Vector2f target, sf::Vector2f position)
		{
			return getTargetAngle(target.x, target.y, position.x, position.y);
		}
		//Invert a given number.
		float inverse(float n)
		{
			n -= n * 2;
			return n;
		}
		//Convert radians to degrees.
		float radianToDegree(float radian)
		{
			return radian * (180 / PI);
		}
		//Convert degrees to radians.
		float degreeToRadian(float degree)
		{
			return degree * (PI / 180);
		}
	}
	//Writes a message to the standard error stream and exits the program.
	void die(std::string message, int code, Danmaku *game)
	{
		std::cerr << message;
		if (game)
			game->window.close();
		exit(code);
	}
}


/* Copyleft 2013, Anonymous */
