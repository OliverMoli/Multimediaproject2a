#include "pch.h"
#include "DebugDraw.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Err.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "MathHelper.h"


DebugDraw::DebugDraw() :
	m_enabled(false)
{
	if (!m_font.loadFromFile("../assets/arial.ttf"))
	{
		sf::err() << "Could not load font\n";
	}
};

void DebugDraw::drawLine(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Color& color, const float thickness)
{
	auto dir = p2 - p1;
	const auto length = MathHelper::length(dir);

	if (length >= 1.0f)
	{
		dir = (dir / length) * thickness * 0.5f;
		const sf::Vector2f right(dir.y, -dir.x);

		std::shared_ptr<sf::ConvexShape> shape(new sf::ConvexShape());
		shape->setPointCount(4);
		shape->setPoint(0, p1 - right);
		shape->setPoint(1, p1 + right);
		shape->setPoint(2, p2 + right);
		shape->setPoint(3, p2 - right);
		shape->setFillColor(color);

		m_shapes.push_back(shape);
	}
}

void DebugDraw::drawArrow(const sf::Vector2f& origin, const sf::Vector2f& direction, const sf::Color& color, const float thickness)
{
	const auto length = MathHelper::length(direction);

	if (length >= 1.0f)
	{
		const auto unit_direction = direction / length;
		const sf::Vector2f right(unit_direction.y, -unit_direction.x);

		const auto head_size = 5.0f;
		const auto head = length > (head_size * 2) ? length - head_size : length * 0.5f;

		const auto p1 = origin;
		const auto p2 = origin + unit_direction * head;
		const auto p3 = origin + direction;

		std::shared_ptr<sf::ConvexShape> shape(new sf::ConvexShape());
		shape->setPointCount(4);

		shape->setPoint(0, p1 - right * thickness * 0.5f);
		shape->setPoint(1, p1 + right * thickness * 0.5f);
		shape->setPoint(2, p2 + right * thickness * 0.5f);
		shape->setPoint(3, p2 - right * thickness * 0.5f);
		shape->setFillColor(color);

		m_shapes.push_back(shape);

		std::shared_ptr<sf::ConvexShape> head_shape(new sf::ConvexShape());
		head_shape->setPointCount(3);

		head_shape->setPoint(0, p2 - right * head_size);
		head_shape->setPoint(1, p2 + right * head_size);
		head_shape->setPoint(2, p3);
		head_shape->setFillColor(color);

		m_shapes.push_back(head_shape);
	}
}

void DebugDraw::drawCircle(const sf::Vector2f& center, const float radius, const sf::Color& outline_color, const sf::Color& fill_color)
{
	std::shared_ptr<sf::CircleShape> shape(new sf::CircleShape(radius));
	shape->setOutlineThickness(1.0f);
	shape->setOutlineColor(outline_color);
	shape->setFillColor(fill_color);
	shape->setPosition(center);
	shape->setOrigin(sf::Vector2f(radius, radius));

	m_shapes.push_back(shape);
}

void DebugDraw::drawRectangle(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& outline_color,
	const sf::Color& fill_color)
{
	std::shared_ptr<sf::RectangleShape> shape(new sf::RectangleShape(size));
	shape->setOutlineThickness(1.0f);
	shape->setOutlineColor(outline_color);
	shape->setFillColor(fill_color);
	shape->setPosition(position);

	m_shapes.push_back(shape);
}

void DebugDraw::drawText(const std::string& str, const sf::Vector2f& center, const sf::Color& color)
{
	std::shared_ptr<sf::Text> text(new sf::Text());
	text->setPosition(center);
	text->setString(str);
	text->setFillColor(color);
	text->setFont(m_font);
	text->setCharacterSize(14);
	const auto bounds = text->getLocalBounds();
	text->setOrigin(bounds.width * 0.5f,bounds.height * 0.5f + bounds.top);

	m_shapes.push_back(text);
}

void DebugDraw::update(float delta_time)
{
	m_shapes.clear();
}

void DebugDraw::draw(sf::RenderWindow& render_window)
{
	if (m_enabled)
	{
		for (const auto& shape : m_shapes)
		{
			render_window.draw(*shape);
		}
	}
}

void DebugDraw::freeResources()
{
	m_shapes.clear();
}
