#include "pch.h"
#include "MathHelper.h"

sf::Vector2f MathHelper::getNormalizedVec2f(sf::Vector2f in)
{
	float normFactor = length(in);
	if (normFactor != 0) {
		return in / normFactor;
	}
	else { return in; }
}

void MathHelper::normalizeVec2f(sf::Vector2f & in)
{
	float normFactor = length(in);
	if (normFactor != 0) {
		in /= normFactor;
	}
}

float MathHelper::length(sf::Vector2f in)
{
	return sqrt(in.x*in.x + in.y*in.y);
}

float MathHelper::random(float rangeFrom, float rangeTo)
{
	float r = (float)rand() / (float)RAND_MAX;
	return rangeFrom + r * (rangeTo - rangeFrom);
}

void MathHelper::truncate(sf::Vector2f & in, float maxLength)
{
	if (length(in) > maxLength)
	{
		normalizeVec2f(in);
		in *= maxLength;
	}
}

sf::Vector2f MathHelper::getInverseVector(sf::Vector2f in)
{
	in.x = -in.x;
	in.y = -in.y;
	return in;
}

sf::Vector2f MathHelper::getRandomDir()
{
	return sf::Vector2f(random(-1, 1), random(-1, 1));
}

float MathHelper::getAngle(sf::Vector2f a, sf::Vector2f b)
{
	float dot = a.x * b.x + a.y * b.y;
	float det = a.x * b.y - a.y * b.x;
	float angle = atan2(det, dot);
	float deg = angle * 180 / (atan(1) * 4);
	if(deg <0)
	{
		deg = 180 - deg;
	}
	return deg;
}

sf::Vector2f MathHelper::getVectorFromAngle(float angle)
{
	return sf::Vector2f(cos(angle), sin(angle));
}


