#pragma once
#include <SFML/System/Vector2.hpp>

class MathHelper
{
public:
	static sf::Vector2f getNormalizedVec2f(sf::Vector2f in);
	static void normalizeVec2f(sf::Vector2f& in);
	static float length(sf::Vector2f in);
	static int random(int rangeFrom, int rangeTo);
	static void truncate(sf::Vector2f& in, float maxLength);
	static sf::Vector2f getInverseVector(sf::Vector2f in);
};
