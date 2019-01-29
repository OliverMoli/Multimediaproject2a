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

int MathHelper::random(int rangeFrom, int rangeTo)
{
	return rand() % rangeTo + rangeFrom;
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


