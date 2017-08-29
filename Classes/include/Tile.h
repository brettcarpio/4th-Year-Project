#ifndef TILE_H
#define TILE_H

#include <SFML\Graphics.hpp>

class Tile {
public:
	Tile();
	Tile(sf::Vector2f position, sf::Vector2f size);
	~Tile();

	void Render(sf::RenderWindow & window);
	sf::RectangleShape GetRect();
	sf::Vector2f GetPos();

private:
	
	sf::RectangleShape m_rect;
	sf::Vector2f m_pos;
};

#endif // !TILE_H

