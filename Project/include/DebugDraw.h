#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>

namespace sf {
	class RenderWindow;
}

/// Simple debug draw functionality.
/// Use the relevant Draw* methode to render debug stuff in the current frame
class DebugDraw
{
public:
	static DebugDraw& getInstance()
	{
		static DebugDraw instance;
		return instance;
	}

	void drawLine(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Color& color, float thickness = 1.0f);
	void drawArrow(const sf::Vector2f& origin, const sf::Vector2f& direction, const sf::Color& color, float thickness = 1.0f);
	void drawCircle(const sf::Vector2f& center, float radius, const sf::Color& outline_color, const sf::Color& fill_color = sf::Color::Transparent);
	void drawText(const std::string& text, const sf::Vector2f& center, const sf::Color& color);
	void drawRectangle(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Color& outline_color, const sf::Color& fill_color = sf::Color::Transparent);


	bool isEnabled() const
	{
		return m_enabled;
	}

	void setEnabled(bool enabled)
	{
		m_enabled = enabled;
	}

	void update(float fDeltaTime);

	void draw(sf::RenderWindow& renderWindow);
	void freeResources();
private:
	DebugDraw();

	DebugDraw(DebugDraw const&) {};
	void operator=(DebugDraw const&) {};
	~DebugDraw() {};

	bool m_enabled = false;
	std::vector<std::shared_ptr<sf::Drawable>> m_shapes;
	sf::Font m_font;
};