#pragma once

class GameObject;
class Component
{
public:
	Component(GameObject& owner);
	virtual void initialize()=0;
	virtual void update(float deltaTime)=0;
	///@return The gameobject this component is attached to
	GameObject& getGameObject();
protected:
	GameObject& gameObject;
};
