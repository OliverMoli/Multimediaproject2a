#include "pch.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "SpriteRenderComponent.h"
#include "ResourceManager.h"
#include "GameStateManager.h"
#include "RigidBodyComponent.h"
#include "AABBColliderComponent.h"
#include "FlagComponent.h"
#include "ScoreComponent.h"
#include "MovementComponent.h"
#include "PlayerControllerComponent.h"
#include "Game.h"
#include "BallComponent.h"
#include "PlayFieldComponent.h"


void GameObjectFactory::CreatePlayer(NLTmxMapObject object)
{
	auto playerObject = make_shared<GameObject>(object.name, object.type);

	struct PlayerValues
	{
		string textureName;
		string team;
		sf::Vector2f colOffset;
	};

	PlayerValues values;
	for (auto property : object.properties)
	{
		auto name = property->name;

		if (name == "textureName")
		{
			values.textureName = property->value;
		}
		else if (name == "team")
		{
			values.team = property->value;
		}
		else if (name == "colOffsetX")
		{
			values.colOffset.x = stof(property->value);
		}
		else if (name == "colOffsetY")
		{
			values.colOffset.y = stof(property->value);
		}
	}
	playerObject->setPosition(object.x, object.y);
	playerObject->addComponent(std::make_shared<SpriteRenderComponent>(*playerObject, *ResourceManager::getInstance().getTexture(values.textureName)));
	playerObject->getComponent<SpriteRenderComponent>()->setLayer(Player);
	playerObject->addComponent(std::make_shared<RigidBodyComponent>(*playerObject, 1.0f));
	playerObject->getComponent<RigidBodyComponent>()->setFriction(0.87f);
	playerObject->addComponent(std::make_shared<CharacterInfoComponent>(*playerObject));
	playerObject->addComponent(std::make_shared<AABBColliderComponent>(*playerObject, object.width, object.height, false, values.colOffset));
	playerObject->addComponent(std::make_shared<MovementComponent>(*playerObject, 300000, 500000));
	GameStateManager::getInstance().getCurrentState()->addGameObject(playerObject);

}

void GameObjectFactory::CreateFlag(NLTmxMapObject object)
{
	auto flagObject = make_shared<GameObject>(object.name, object.type);

	struct FlagValues
	{
		string textureName;
		int scorePerTick;
		float tickDuration;
	};

	FlagValues values;
	for (auto property : object.properties)
	{
		auto name = property->name;

		if (name == "textureName")
		{
			values.textureName = property->value;
		}
		else if (name == "tickDuration")
		{
			values.tickDuration = stof(property->value);
		}
		else if (name == "scorePerTick")
		{
			values.scorePerTick = stoi(property->value);
		}
	}

	flagObject->setPosition(object.x, object.y);
	flagObject->addComponent(std::make_shared<SpriteRenderComponent>(*flagObject, *ResourceManager::getInstance().getTexture(values.textureName)));
	flagObject->getComponent<SpriteRenderComponent>()->setLayer(Items);
	flagObject->addComponent(std::make_shared<RigidBodyComponent>(*flagObject, 0));
	flagObject->addComponent(std::make_shared<AABBColliderComponent>(*flagObject, object.width, object.height, true));
	flagObject->addComponent(std::make_shared<FlagComponent>(*flagObject,values.scorePerTick,values.tickDuration));
	flagObject->getComponent<RigidBodyComponent>()->addObserver(flagObject->getComponent<FlagComponent>());
	GameStateManager::getInstance().getCurrentState()->addGameObject(flagObject);
}

void GameObjectFactory::CreateScore()
{
	auto scoreObject = std::make_shared<GameObject>("Score", "Score");
	scoreObject->addComponent(std::make_shared<ScoreComponent>(*scoreObject));
	scoreObject->getComponent<ScoreComponent>()->setLayer(UI);
	scoreObject->setPosition(616, 0);
	GameStateManager::getInstance().getCurrentState()->addGameObject(scoreObject);
}

void GameObjectFactory::CreateBall(NLTmxMapObject object)
{
	auto ballObject = make_shared<GameObject>(object.name, object.type);

	struct BallValues
	{
		string textureName;
		string playField;
	};

	BallValues values;

	for (auto property : object.properties)
	{
		auto name = property->name;

		if (name == "textureName")
		{
			values.textureName = property->value;
		}
		if (name == "playField")
		{
			values.playField = property->value;
		}
	}

	ballObject->setPosition(object.x, object.y);
	ballObject->addComponent(std::make_shared<SpriteRenderComponent>(*ballObject, *ResourceManager::getInstance().getTexture(values.textureName)));
	ballObject->getComponent<SpriteRenderComponent>()->setLayer(Items);
	ballObject->addComponent(std::make_shared<RigidBodyComponent>(*ballObject, 0));
	ballObject->addComponent(std::make_shared<AABBColliderComponent>(*ballObject, object.width, object.height, true));
	ballObject->addComponent(std::make_shared<BallComponent>(*ballObject, values.playField));
	//ballObject->addComponent(std::make_shared<PlayFieldComponent>(*ballObject));
	ballObject->getComponent<RigidBodyComponent>()->addObserver(ballObject->getComponent<BallComponent>());
	GameStateManager::getInstance().getCurrentState()->addGameObject(ballObject);
}

void GameObjectFactory::CreatePlayField(NLTmxMapObject object)
{
	auto playField = make_shared<GameObject>(object.name, object.type);
	playField->setPosition(object.x, object.y);
	playField->addComponent(std::make_shared<PlayFieldComponent>(*playField, object.width, object.height));
	GameStateManager::getInstance().getCurrentState()->addGameObject(playField);

}


bool GameObjectFactory::stob(string value)
{
	if (value == "true")
	{
		return true;
	}
	else if (value == "false")
	{
		return false;
	}
}


