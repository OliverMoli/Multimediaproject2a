#pragma once
#include <SFML/System/Vector2.hpp>

class MathHelper
{
public:
	static sf::Vector2f getNormalizedVec2f(sf::Vector2f in);
	static void normalizeVec2f(sf::Vector2f& in);
	static float length(sf::Vector2f in);
	static float random(float rangeFrom, float rangeTo);
	static void truncate(sf::Vector2f& in, float maxLength);
	static sf::Vector2f getInverseVector(sf::Vector2f in);
	static sf::Vector2f getRandomDir();
	static float getAngle(sf::Vector2f a, sf::Vector2f b);
	static sf::Vector2f getVectorFromAngle(float angle);
};
