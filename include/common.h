#ifndef COMMON_H
#define COMMON_H
#include "main.h"
#include "../include/danmaku.h"


namespace stg
{
	namespace math
	{
		//Returns the distance between two points.
		float distance(float ax, float ay, float bx, float by);
		//Overload the distance function with a different number of parameters.
		float distance(sf::Vector2f a, sf::Vector2f b);
		//Get the angle of a target.
		float getTargetAngle(float target_x, float target_y, float x, float y);
		//Overload the getTargetAngle function with a different number of parameters.
		float getTargetAngle(sf::Vector2f target, sf::Vector2f position);
		//Invert a given number.
		float inverse(float n);
		//Convert radians to degrees.
		float radianToDegree(float radian);
		//Convert degrees to radians.
		float degreeToRadian(float degree);
		
	}
	//Writes a message to the standard error stream and exits the program.
	void die(std::string message = "", int code = 1, Danmaku *game = NULL);
}

#endif

/* Copyleft 2013, Anonymous */
