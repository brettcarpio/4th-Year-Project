#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(sf::Vector2f position, sf::Vector2f size)
{
	m_filled = false;
	m_hasSprite = false;
	m_pos = position;
	m_rect = sf::RectangleShape(size);
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineThickness(0.5f);
	m_rect.setOutlineColor(sf::Color(255, 255, 255, 50));
	m_rect.setPosition(m_pos);
}

Tile::Tile(sf::Vector2f position, sf::Texture * tex)
{
	m_filled = false;
	m_hasSprite = true;
	m_pos = position;
	m_sprite.setTexture(*tex);
	m_sprite.setPosition(m_pos);
}

Tile::~Tile()
{
}

void Tile::Render(sf::RenderWindow & window)
{
	if (m_hasSprite && m_filled)
		window.draw(m_sprite);
	else
		window.draw(m_rect);
}

sf::RectangleShape Tile::GetRect()
{
	return m_rect;
}

sf::Vector2f Tile::GetPos()
{
	return m_pos;
}

void Tile::FillTile()
{
	m_rect.setFillColor(sf::Color::Cyan);
	m_filled = true;
}

void Tile::UnFillTile()
{
	m_rect.setFillColor(sf::Color::Transparent);
	m_filled = false;
}

bool Tile::IsFilled() const
{
	return m_filled;
}
