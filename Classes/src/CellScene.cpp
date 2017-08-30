#include "CellScene.h"

CellScene::CellScene(sf::RenderWindow & window) : Scene("CellScene", false, sceneswitch(false, ""))
{
	SetupGraph();
	SetupGrammar();
	m_grid = Grid(sf::Vector2f(16, 16), sf::Vector2f(0, 0), (window.getSize().x / 16), (window.getSize().y / 16));
	m_grid.SetVisible(false);
}

CellScene::~CellScene()
{
}

void CellScene::Update(sf::Time dt)
{
}

void CellScene::Render(sf::RenderWindow & window)
{
	for (Grid g : m_grids)
		g.Render(window);
	m_grid.Render(window);
}

void CellScene::HandleInput(sf::Event e)
{
	if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Num1))
	{
		m_switchingScene = sceneswitch(true, "MenuScene");
	}
	else if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Num2))
	{
		m_switchingScene = sceneswitch(true, "DungeonScene");
	}
	else if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::G))
	{
		if (m_grid.IsVisible())
			m_grid.SetVisible(false);
		else
			m_grid.SetVisible(true);
	}
	else if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Space))
	{
		ClearDrawables();
		RenderDungeon();
	}
	else if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::F))
	{
		if (!m_grids.empty())
			EvolveMap(m_grids.at(0));
	}
}

void CellScene::Start()
{
	m_alive = true;
	SetupGraph();
	SetupGrammar();
}

void CellScene::Stop()
{
	m_alive = false;
	m_grid.SetVisible(false);
	m_switchingScene = sceneswitch(false, "");
}

void CellScene::SetupGraph()
{
	int noOfNodes = 0;

	std::ifstream file;

	m_graph = new Graph<int, std::string>();

	file.open("Assets/DungeonScene/Graph/nodes.txt");
	std::string data;
	
	while (file >> data)
	{
		m_graph->AddNode(data, 0);
	}
	file.close();

	file.open("Assets/DungeonScene/Graph/arcs.txt");
	int from, to;
	while (file >> from >> to)
	{
		m_graph->AddArc(from, to, "");
	}
	file.close();
}

void CellScene::SetupGrammar()
{
	m_grammar = GrammarSystem<int, std::string>();
	m_grammar.CreateRules("Assets/CellScene/Graph/rules.txt");
}

void CellScene::RenderDungeon()
{
	Grid grid = Grid(sf::Vector2f(8, 8), sf::Vector2f(32, 32), 30, 30);
	CreateGrid(grid);
	m_grids.push_back(grid);
}

void CellScene::ClearDrawables()
{
	int gridsSize = m_grids.size();
	for (int i = 0; i < gridsSize; i++)
	{
		m_grids.erase(m_grids.begin());
	}
}

void CellScene::CreateGrid(Grid &g)
{
	const int chance = 40;
	for (int row = 0; row < g.GetNumberOfRows(); row++)
	{
		for (int col = 0; col < g.GetNumberOfCols(); col++)
		{
			if (row == 0 || col == 0 || (row == g.GetNumberOfRows() - 1) || (col == g.GetNumberOfCols() - 1))
			{
				g.GetTiles()[row][col].FillTile();
			}
			else
			{
				int middle = g.GetNumberOfCols() / 2;
				if (row == middle)
					g.GetTiles()[row][col].UnFillTile();
				else if ((rand() % 101) < chance)
					g.GetTiles()[row][col].FillTile();
			}
		}
	}
}

void CellScene::EvolveMap(Grid &g)
{
	for (int row = 1; row <= g.GetNumberOfRows() - 1; row++)
	{
		for (int col = 1; col <= g.GetNumberOfCols() - 1; col++)
		{
			if (PlaceWallLogic(g, row, col))
				g.GetTiles()[row][col].FillTile();
			else
				g.GetTiles()[row][col].UnFillTile();
		}
	}
}

bool CellScene::PlaceWallLogic(Grid &g, int row, int col)
{
	int numWalls = GetSurroundingWalls(g, row, col);
	//int numWalls2 = GetSurroundingWalls(g, row, col);

	if (g.GetTiles()[row][col].IsFilled())
	{
		return (numWalls >= 3) ? true : false;
	}
	else
	{
		if (numWalls >= 5) {
			return true;
		}
	}
	return false;
}

int CellScene::GetSurroundingWalls(Grid &g, int row, int col)
{
	int startX = row - 1;
	int startY = col - 1;
	int endX = row + 1;
	int endY = col + 1;

	int wallCounter = 0;

	for (int i = startX; i <= endX; i++) 
	{
		for (int j = startY; j <= endY; j++)
		{
			if (!(i == row && j == col))
			{
				if (IsWall(g, i, j))
				{
					wallCounter++;
				}
			}
		}
	}
	return wallCounter;
}

bool CellScene::IsWall(Grid & g, int row, int col)
{
	return (IsOutOfBound(g, row, col) || g.GetTiles()[row][col].IsFilled());
}

bool CellScene::IsOutOfBound(Grid & g, int row, int col)
{
	return (row < 0 || col < 0 || row > g.GetNumberOfRows() - 1 || col > g.GetNumberOfCols() - 1);
}
