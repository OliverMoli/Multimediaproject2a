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
#include "StunStarComponent.h"


void GameObjectFactory::CreatePlayer(NLTmxMapObject object)
{
	auto playerObject = make_shared<GameObject>(object.name, object.type);

	struct PlayerValues
	{
		string textureName;
		string team;
		sf::Vector2f colOffset;
		float normalMaxVelocity;
		float normalMaxSteeringForce;
		float flagHolderMaxVelocity;
		float flagHolderMaxSteeringForce;
		float normalDashForce;
		float normalDashCooldown;
		float flagHolderDashForce;
		float flagHolderDashCooldown;
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
		else if (name == "normalMaxVelocity")
		{
			values.normalMaxVelocity = stof(property->value);
		}
		else if (name == "normalMaxSteeringForce")
		{
			values.normalMaxSteeringForce = stof(property->value);
		}
		else if (name == "flagHolderMaxVelocity")
		{
			values.flagHolderMaxVelocity = stof(property->value);
		}
		else if (name == "flagHolderMaxSteeringForce")
		{
			values.flagHolderMaxSteeringForce = stof(property->value);
		}
		else if (name == "normalDashCooldown")
		{
			values.normalDashCooldown = stof(property->value);
		}
		else if (name == "normalDashForce")
		{
			values.normalDashForce = stof(property->value);
		}
		else if (name == "flagHolderDashCooldown")
		{
			values.flagHolderDashCooldown = stof(property->value);
		}
		else if (name == "flagHolderDashForce")
		{
			values.flagHolderDashForce = stof(property->value);
		}
	};

	playerObject->setPosition(object.x, object.y);
	playerObject->addComponent(std::make_shared<SpriteRenderComponent>(*playerObject, *ResourceManager::getInstance().getTexture(values.textureName)));
	playerObject->getComponent<SpriteRenderComponent>()->setLayer(Player);
	playerObject->addComponent(std::make_shared<RigidBodyComponent>(*playerObject, 1.0f));
	playerObject->getComponent<RigidBodyComponent>()->setFriction(0.87f);
	playerObject->addComponent(std::make_shared<CharacterInfoComponent>(*playerObject));
	playerObject->addComponent(std::make_shared<AABBColliderComponent>(*playerObject, object.width, object.height, false, values.colOffset));
	playerObject->addComponent(std::make_shared<MovementComponent>(*playerObject, values.normalMaxVelocity, values.normalMaxSteeringForce, values.flagHolderMaxVelocity, values.flagHolderMaxSteeringForce,values.normalDashForce,values.normalDashCooldown,values.flagHolderDashForce,values.flagHolderDashCooldown));
	//playerObject->addComponent(std::make_shared<SpriteAnimationComponent>(*playerObject, *ResourceManager::getInstance().getTexture(values.textureName), object.x, object.y));
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
	flagObject->getComponent<SpriteRenderComponent>()->setLayer(UI);
	flagObject->addComponent(std::make_shared<RigidBodyComponent>(*flagObject, 1));
	flagObject->getComponent<RigidBodyComponent>()->setFriction(0.9);
	flagObject->addComponent(std::make_shared<AABBColliderComponent>(*flagObject, object.width, object.height, false));
	flagObject->addComponent(std::make_shared<FlagComponent>(*flagObject, values.scorePerTick, values.tickDuration));
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
		float ballVelocityPerCharge;
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
		else if (name == "ballVelocityPerCharge")
		{
			values.ballVelocityPerCharge = stof(property->value);
		}
		else if (name == "resetLastDelay")
		{
			values.resetLastDelay = stof(property->value);
		}
		else if (name == "friction")
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
		}
		else if (name == "velocityFactorOnEnemyHit")
		{
			values.velocityFactorOnEnemyHit = stof(property->value);
		}

	}

	auto arrow1 = make_shared<GameObject>();

	arrow1->addComponent(std::make_shared<SpriteRenderComponent>(*arrow1, *ResourceManager::getInstance().getTexture("marker"), 0, 0, true));
	arrow1->getComponent<SpriteRenderComponent>()->setLayer(Items);
	GameStateManager::getInstance().getCurrentState()->addGameObject(arrow1);
	auto arrow2 = make_shared<GameObject>();

	arrow2->addComponent(std::make_shared<SpriteRenderComponent>(*arrow2, *ResourceManager::getInstance().getTexture("marker"), 0, 0, true));
	arrow2->getComponent<SpriteRenderComponent>()->setLayer(Items);
	GameStateManager::getInstance().getCurrentState()->addGameObject(arrow2);

	ballObject->setPosition(object.x, object.y);
	ballObject->addComponent(std::make_shared<SpriteRenderComponent>(*ballObject, *ResourceManager::getInstance().getTexture(values.textureName)));
	ballObject->getComponent<SpriteRenderComponent>()->setLayer(Items);
	ballObject->addComponent(std::make_shared<RigidBodyComponent>(*ballObject, 1));
	ballObject->addComponent(std::make_shared<AABBColliderComponent>(*ballObject, object.width, object.height, false));
	ballObject->addComponent(std::make_shared<BallComponent>(*ballObject, values.playField, values.ballVelocityPerCharge, values.resetLastDelay, values.stunDurationPerCharge, values.neutralVelocityCutoff, values.velocityFactorOnEnemyHit,*arrow1,*arrow2));
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

void GameObjectFactory::CreateStunStar(GameObject* object, float duration)
{
	auto star = make_shared<GameObject>("star", "star");
	star->addComponent(std::make_shared<SpriteRenderComponent>(*star, *ResourceManager::getInstance().getTexture("stunStars")));
	star->getComponent<SpriteRenderComponent>()->setLayer(UI);
	star->addComponent(std::make_shared<StunStarComponent>(*star, duration));
	star->setPosition(object->getPosition() + sf::Vector2f(2.5,-20));
	star->getComponent<StunStarComponent>()->initAnims("star");
	GameStateManager::getInstance().getCurrentState()->addGameObject(star);
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


