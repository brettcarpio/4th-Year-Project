#ifndef GRID_H
#define GRID_H

#include "Tile.h"

#include <vector>

class Grid {
public:
	Grid();
	Grid(sf::Vector2f tileSize, sf::Vector2f windowSize);
	~Grid();

	void Render(sf::RenderWindow & window);
	bool IsVisible();
	void SetVisible(bool value);

private:
	std::vector<std::vector<Tile>> m_tiles;
	bool m_visible;
	int m_numberOfCols;
	int m_numberOfRows;

};

#endif // !GRID_H

