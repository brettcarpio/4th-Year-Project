#ifndef GRID_H
#define GRID_H

#include "Tile.h"

#include <vector>

class Grid {
public:
	Grid();
	Grid(sf::Vector2f tileSize, sf::Vector2f startPos, int numberOfRows, int numberOfCols);
	~Grid();

	void Render(sf::RenderWindow & window);
	bool IsVisible() const;
	void SetVisible(bool value);
	int GetNumberOfRows() const;
	int GetNumberOfCols() const;
	std::vector<std::vector<Tile>> & GetTiles();

private:
	std::vector<std::vector<Tile>> m_tiles;
	bool m_visible;
	int m_numberOfCols;
	int m_numberOfRows;

};

#endif // !GRID_H

