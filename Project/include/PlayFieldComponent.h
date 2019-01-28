#pragma once
#include "Component.h"

class PlayFieldComponent : public Component
{
public:
	PlayFieldComponent(GameObject& owner, int width, int height);
	void initialize() override;
	void update(float deltaTime) override;
	int getWidth() const;
	int getHeight() const;
private:
	int width, height;
};
