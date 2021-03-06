#pragma once
#include "NLTmxMap.h"

class GameObject;

class GameObjectFactory
{
public:
	static bool stob(std::string value);
	static void CreatePlayer(NLTmxMapObject object);
	static void CreateFlag(NLTmxMapObject object);
	static void CreateScore();
	static void CreateBall(NLTmxMapObject object);
	static void CreatePlayField(NLTmxMapObject object);
	static void CreateObstacle(NLTmxMapObject object);
	static void CreateStunStar(GameObject* object, float duration);
};
