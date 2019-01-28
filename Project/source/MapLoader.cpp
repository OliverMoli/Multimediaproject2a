#include "pch.h"
#include "GameObject.h"
#include <SFML/Graphics/Sprite.hpp>
#include "NLTmxMap.h"
#include <SFML/System/Err.hpp>
#include <SFML/System/FileInputStream.hpp>
#include "MapLoader.h"
#include "GameStateManager.h"
#include "LayerComponent.h"
#include "GameObjectFactory.h"

void MapLoader::loadMap(const std::string& filename, const sf::Vector2f & offset)
{
	auto mapObject = std::make_shared<GameObject>("Map","Map");
	sf::FileInputStream mapStream;
	if (!mapStream.open("../assets/" + filename))
	{
		sf::err() << "loadMap: could not open file " << "../assets/" + filename << endl;
		return;
	}

	// convert FileInputStream to char* mapBuffer
	char* mapBuffer = new char[mapStream.getSize() + 1];
	mapStream.read(mapBuffer, mapStream.getSize());
	mapBuffer[mapStream.getSize()] = '\0';

	// now lets load a NLTmxMap
	NLTmxMap* tilemap = NLLoadTmxMap(mapBuffer);
	delete mapBuffer;

	sf::err() << "Load tilemap with size: " << tilemap->width << ", "
		<< tilemap->height << " and tilesize: " << tilemap->tileWidth
		<< ", " << tilemap->tileHeight << std::endl;

	// load textures for every tileset
	for (auto tileset : tilemap->tilesets)
	{
		sf::err() << "Load tileset: " << tileset->name << " width filename: "
			<< tileset->filename << " and tilesize: " << tileset->tileWidth
			<< ", " << tileset->tileHeight << std::endl;
		ResourceManager::getInstance().loadTexture(tileset->name, "../assets/" + tileset->filename);
	}

	// go through all layers
	for (int layerIdx = 0; layerIdx < (int)tilemap->layers.size(); layerIdx++)
	{
		NLTmxMapLayer* layer = tilemap->layers[layerIdx];
		sf::err() << "Load layer: " << layer->name << " with width: "
			<< layer->width << " and height: " << layer->height << std::endl;

		int size = layer->width * layer->height;
		auto layerComp = std::make_shared<LayerComponent>(*mapObject, (RenderLayer)layerIdx);
		mapObject->addComponent(layerComp);
		// go over all elements in the layer
		for (int i = 0; i < size; i++)
		{
			int tile = layer->data[i];

			if (tile == 0)
			{
				// 0 means there is no tile at this grid position.

				// This continue also indicates that the layers are not 
				// represented as two-dimensional arrays, but 
				// only a list of tiles sorted by position from top left
				// to bottom right. (Hint: position could be useful for 
				// quickly finding, which tiles to cull from current 
				// viewport.)					
				continue;
			}

			// get tileset and tileset texture
			NLTmxMapTileset* tileset = tilemap->getTilesetForTile(tile);
			sf::Vector2i tileSize(tilemap->tileWidth, tilemap->tileHeight);
			sf::Texture& texture = *ResourceManager::getInstance().getTexture(tileset->name);

			// horizontal tile count in tileset texture
			int tileCountX = texture.getSize().x / tileSize.x;

			// calcualte position of tile
			sf::Vector2f position;
			position.x = (i % layer->width) * (float)tileSize.x;
			position.y = (i / layer->width) * (float)tileSize.y;
			position += offset;

			// calculate 2d idx of tile in tileset texture
			int idx = tile - tileset->firstGid;
			int idxX = idx % tileCountX;
			int idxY = idx / tileCountX;

			// calculate source area of tile in tileset texture
			sf::IntRect source(idxX * tileSize.x, idxY * tileSize.y, tileSize.x, tileSize.y);

			auto sprite = std::make_shared<sf::Sprite>(texture, source);
			sprite->setPosition(position);
			layerComp->addSprite(sprite);


		}
	}

	// go through all object layers
	for (auto group : tilemap->groups)
	{
		// go over all objects per layer
		for (auto object : group->objects)
		{
			auto go = std::make_shared<GameObject>();
			if (object->type == "Player")
			{
				GameObjectFactory::CreatePlayer(*object);
			}
			else if (object->type == "Flag")
			{
				GameObjectFactory::CreateFlag(*object);
			}
			else if (object->type == "Ball")
			{
				GameObjectFactory::CreateBall(*object);
			}
			//TODO: Call helper functions for creatin objects here
		}
	}

	GameStateManager::getInstance().getCurrentState()->addGameObject(mapObject);
}

MapLoader& MapLoader::getInstance()
{
	static MapLoader instance;
	return instance;
}
