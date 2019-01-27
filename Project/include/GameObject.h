#pragma once
#include <SFML/Graphics/Transformable.hpp>
#include "Component.h"
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject : public sf::Transformable
{
public:
	GameObject();
	GameObject(std::string name, std::string type);
	void update(float deltaTime);
	///Adds a component to the gameobject
	///@param comp The component to add
	void addComponent(std::shared_ptr<Component> comp);
	///@return The first component of type T attached to this gameobject
	template <typename T>
	std::shared_ptr<T> getComponent()
	{
		for (auto component : components)
		{
			std::shared_ptr<T> cmp = std::dynamic_pointer_cast<T>(component);
			if (cmp != nullptr)
			{
				return cmp;
			}
		}
		return nullptr;
	}
	///@return All components of type T attached to this gameobject
	template <typename T>
	std::vector<std::shared_ptr<T>> getComponents()
	{
		std::vector<std::shared_ptr<T>> result;
		for (auto component : components)
		{
			std::shared_ptr<T> cmp = std::dynamic_pointer_cast<T>(component);
			if (cmp != nullptr)
			{
				result.push_back(cmp);
			}
		}
		return result;
	}
	///Marks a component for deletion
	///@param comp The Component to be deleted
	void markComponentForDeletion(std::shared_ptr<Component> comp);
	///Deletes marked Components
	void deleteMarkedComponents();

	std::string getName() const;
	std::string getType() const;
	void setActive(bool active);
	bool isActive() const;
private:
	std::vector<std::shared_ptr<Component>> components;
	std::vector<std::shared_ptr<Component>> componentsToDelete;
	std::string name;
	std::string type;
	bool active = true;
};
