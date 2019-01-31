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
#include "SpriteAnimationComponent.h"


void GameObjectFactory::CreatePlayer(NLTmxMapObject object)
{
	auto playerObject = make_shared<GameObject>(object.name, object.type);

	struct PlayerValues
	{
		string textureName;
		string team;
		sf::Vector2f colOffset;
		float dashForce;
		float dashCooldown;

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
		else if (name == "dashForce")
		{
			values.dashForce = stof(property->value);	
		}
		else if (name == "dashCooldown")
		{
			values.dashCooldown = stof(property->value);
		}
	};

	playerObject->setPosition(object.x, object.y);
	playerObject->addComponent(std::make_shared<SpriteRenderComponent>(*playerObject, *ResourceManager::getInstance().getTexture(values.textureName)));
	playerObject->getComponent<SpriteRenderComponent>()->setLayer(Player);
	playerObject->addComponent(std::make_shared<RigidBodyComponent>(*playerObject, 1.0f));
	playerObject->getComponent<RigidBodyComponent>()->setFriction(0.87f);
	playerObject->addComponent(std::make_shared<CharacterInfoComponent>(*playerObject, values.dashForce, values.dashCooldown));
	playerObject->addComponent(std::make_shared<AABBColliderComponent>(*playerObject, object.width, object.height, false, values.colOffset));
	playerObject->addComponent(std::make_shared<MovementComponent>(*playerObject, 300000, 500000));
	playerObject->addComponent(std::make_shared<SpriteAnimationComponent>(*playerObject, *ResourceManager::getInstance().getTexture(values.textureName), object.x, object.y));
	playerObject->getComponent<SpriteAnimationComponent>()->animate(*ResourceManager::getInstance().getTexture(values.textureName));
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
		float ballSpeed;
		float resetLastDelay;
		float friction;
		float stunDurationPerCharge;
		float neutralVelocityCutoff;
		float velocityFactorOnEnemyHit;
	};

	BallValues values;

	for (auto property : object.properties)
	{
		auto name = property->name;

		if (name == "textureName")
		{
			values.textureName = property->value;
		}
		else if (name == "playField")
		{
			values.playField = property->value;
		}
		else if(name == "ballSpeed")
		{
			values.ballSpeed = stof(property->value);
		}else if(name =="resetLastDelay")
		{
			values.resetLastDelay = stof(property->value);
		}else if(name == "friction")
		{
			values.friction = stof(property->value);
		}
		else if (name == "stunDurationPerCharge")
		{
			values.stunDurationPerCharge = stof(property->value);
		}
		else if (name == "neutralVelocityCutoff")
		{
			values.neutralVelocityCutoff = stof(property->value);
		}else if (name == "velocityFactorOnEnemyHit")
		{
			values.velocityFactorOnEnemyHit = stof(property->value);
		}
		
	}

	ballObject->setPosition(object.x, object.y);
	ballObject->addComponent(std::make_shared<SpriteRenderComponent>(*ballObject, *ResourceManager::getInstance().getTexture(values.textureName)));
	ballObject->getComponent<SpriteRenderComponent>()->setLayer(Items);
	ballObject->addComponent(std::make_shared<RigidBodyComponent>(*ballObject, 1));
	ballObject->addComponent(std::make_shared<AABBColliderComponent>(*ballObject, object.width, object.height, false));
	ballObject->addComponent(std::make_shared<BallComponent>(*ballObject, values.playField, values.ballSpeed,values.resetLastDelay,values.stunDurationPerCharge,values.neutralVelocityCutoff,values.velocityFactorOnEnemyHit));
	ballObject->getComponent<RigidBodyComponent>()->addObserver(ballObject->getComponent<BallComponent>());
	ballObject->getComponent<RigidBodyComponent>()->setFriction(values.friction);
	GameStateManager::getInstance().getCurrentState()->addGameObject(ballObject);
}

void GameObjectFactory::CreatePlayField(NLTmxMapObject object)
{
	auto playField = make_shared<GameObject>(object.name, object.type);
	playField->setPosition(object.x, object.y);
	playField->addComponent(std::make_shared<PlayFieldComponent>(*playField, object.width, object.height));
	GameStateManager::getInstance().getCurrentState()->addGameObject(playField);

}

void GameObjectFactory::CreateObstacle(NLTmxMapObject object)
{
	auto obstacle = make_shared<GameObject>(object.name, object.type);
	obstacle->setPosition(object.x, object.y);
	obstacle->addComponent(std::make_shared<RigidBodyComponent>(*obstacle, 0));
	obstacle->addComponent(std::make_shared<AABBColliderComponent>(*obstacle, object.width, object.height, false, sf::Vector2f(0, 0)));
	GameStateManager::getInstance().getCurrentState()->addGameObject(obstacle);
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


