#pragma once
#include <SFML/Graphics.hpp>

class MapLoader
{
public:
	///Loads the map with the given filename
	void loadMap(const std::string& filename, const sf::Vector2f& offset);
	static MapLoader& getInstance();
private:
	MapLoader() = default;
	~MapLoader() = default;
	MapLoader(const MapLoader& p) = delete;
	MapLoader& operator=(const MapLoader& rhs) = delete;


};