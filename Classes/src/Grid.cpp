#include "Grid.h"

Grid::Grid()
{
}

Grid::Grid(sf::Vector2f tileSize, sf::Vector2f windowSize)
{
	m_visible = false;
	m_numberOfRows = windowSize.x / tileSize.x;
	m_numberOfCols = windowSize.y / tileSize.y;

	float xPos = 0;

	for (int i = 0; i < m_numberOfRows; i++)
	{
		std::vector<Tile> row;
		float yPos = 0;
		for (int j = 0; j < m_numberOfCols; j++) {
			Tile tile(sf::Vector2f(xPos, yPos), tileSize);
			row.push_back(tile);
			yPos += tileSize.y;
		}
		m_tiles.push_back(row);
		xPos += tileSize.x;
	}
}

Grid::~Grid()
{
}

void Grid::Render(sf::RenderWindow & window)
{
	if (m_visible)
	{
		for (int i = 0; i < m_numberOfRows; i++)
		{
			for (int j = 0; j < m_numberOfCols; j++) {
				m_tiles[i][j].Render(window);
			}
		}
	}
}

bool Grid::IsVisible()
{
	return m_visible;
}

void Grid::SetVisible(bool value)
{
	m_visible = value;
}
