#include "pch.h"
#include "PlayFieldComponent.h"

PlayFieldComponent::PlayFieldComponent(GameObject & owner, int width, int height) :Component(owner)
{
	this->width = width;
	this->height = height;
}

void PlayFieldComponent::initialize()
{

}

void PlayFieldComponent::update(float deltaTime)
{
}

int PlayFieldComponent::getWidth() const
{
	return width;
}

int PlayFieldComponent::getHeight() const
{
	return height;
}