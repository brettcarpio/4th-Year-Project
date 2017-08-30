#include "Grid.h"

Grid::Grid()
{
}

Grid::Grid(sf::Vector2f tileSize, sf::Vector2f startPos, int numberOfRows, int numberOfCols)
{
	m_visible = true;
	m_numberOfRows = numberOfRows;
	m_numberOfCols = numberOfCols;

	int xPos = startPos.x;
	for (int i = 0; i < m_numberOfRows; i++)
	{
		std::vector<Tile> row;
		int yPos = startPos.y;
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

bool Grid::IsVisible() const
{
	return m_visible;
}

void Grid::SetVisible(bool value)
{
	m_visible = value;
}

int Grid::GetNumberOfRows() const
{
	return m_numberOfRows;
}

int Grid::GetNumberOfCols() const
{
	return m_numberOfCols;
}

std::vector<std::vector<Tile>> & Grid::GetTiles()
{
	return m_tiles;
}
