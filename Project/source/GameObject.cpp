#include "pch.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "RenderManager.h"
#include "RigidBodyComponent.h"
#include "PhysicsManager.h"

GameObject::GameObject()
{
}

GameObject::GameObject(std::string name,std::string type)
{
	this->name = name;
	this->type = type;
}

void GameObject::update(float deltaTime)
{
	for (auto comp : components)
	{
		comp->update(deltaTime);
	}
	deleteMarkedComponents();
}

void GameObject::addComponent(std::shared_ptr<Component> comp)
{
	{
		std::shared_ptr<RenderComponent> cmp = std::dynamic_pointer_cast<RenderComponent>(comp);
		if (cmp != nullptr)
		{
			RenderManager::getInstance().addRenderComponent(cmp);
		}
	} 
	{
		std::shared_ptr<RigidBodyComponent> cmp = std::dynamic_pointer_cast<RigidBodyComponent>(comp);
		if (cmp != nullptr)
		{
			PhysicsManager::getInstance().addRigidbodyComponent(cmp);
		}
	}
	{
		std::shared_ptr<ColliderComponent> cmp = std::dynamic_pointer_cast<ColliderComponent>(comp);
		if (cmp != nullptr)
		{
			if(cmp->getGameObject().getComponent<RigidBodyComponent>()==nullptr)
			{
				std::cout << "Error! Could not add ColliderComponent as the target gameobject does not have a rigidbody attached" << std::endl;
				return;
			}else
			{
				cmp->getGameObject().getComponent<RigidBodyComponent>()->addCollider(cmp);
			}
		}
	}
	components.push_back(comp);
	comp->initialize();
}

void GameObject::markComponentForDeletion(std::shared_ptr<Component> comp)
{
		componentsToDelete.push_back(comp);
}

void GameObject::deleteMarkedComponents()
{
	for(auto comp : componentsToDelete)
	{
		auto it = std::find(components.begin(), components.end(), comp);
		if (it != components.end())
		{
			components.erase(it);
		}
	}
}

std::string GameObject::getName() const
{
	return name;
}

std::string GameObject::getType() const
{
	return type;
}


void GameObject::setActive(bool active)
{
	this->active = active;
}

bool GameObject::isActive() const
{
	return active;
}
