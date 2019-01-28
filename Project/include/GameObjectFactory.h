#pragma once
#include "NLTmxMap.h"

class GameObjectFactory
{
public:
	static bool stob(std::string value);
	static void CreatePlayer(NLTmxMapObject object);
};
