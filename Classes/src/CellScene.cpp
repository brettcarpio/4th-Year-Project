#include "CellScene.h"

CellScene::CellScene(sf::RenderWindow & window) : Scene("CellScene", false, sceneswitch(false, ""))
{
	SetupGraph();
	SetupGrammar();
	m_grid = Grid(sf::Vector2f(12, 12), sf::Vector2f(0, 0), (window.getSize().x / 12), (window.getSize().y / 11));

	if (!m_logoTexture.loadFromFile("Assets/CellScene/Assets/logo.png"))
		std::cout << "logo not loaded!" << std::endl;
	if (!m_dungeonBtnTex.loadFromFile("Assets/CellScene/Assets/Dungeon_btn.png"))
		std::cout << "C.A button not loaded!" << std::endl;
	if (!m_mainBtnTex.loadFromFile("Assets/CellScene/Assets/main_btn.png"))
		std::cout << "main button not loaded!" << std::endl;
	if (!m_generateBtnTex.loadFromFile("Assets/CellScene/Assets/generate.png"))
		std::cout << "generate button not loaded!" << std::endl;

	m_mainBtn.setTexture(m_mainBtnTex);
	m_mainBtn.setPosition(window.getSize().x - 350, 550);

	m_dungeonBtn.setTexture(m_dungeonBtnTex);
	m_dungeonBtn.setPosition(window.getSize().x - 350, 650);

	m_logo.setTexture(m_logoTexture);
	m_logo.setPosition(m_mainBtn.getPosition().x - 50, 25);

	m_generateBtn.setTexture(m_generateBtnTex);
	m_generateBtn.setPosition(window.getSize().x - 350, 250);

	m_sprites.push_back(m_logo);
	m_sprites.push_back(m_mainBtn);
	m_sprites.push_back(m_generateBtn);
	m_sprites.push_back(m_dungeonBtn);
}

CellScene::~CellScene()
{
	RestartScene();
}

void CellScene::Update(sf::Time dt)
{
}

void CellScene::Render(sf::RenderWindow & window)
{
	for (Grid g : m_grids)
		g.Render(window);
	for (sf::Sprite s : m_sprites)
		window.draw(s);
	m_grid.Render(window);
	mousepos = sf::Mouse::getPosition(window);
}

void CellScene::HandleInput(sf::Event e)
{
	if (mousepos.x >= (m_mainBtn.getPosition().x) &&
		mousepos.x <= (m_mainBtn.getPosition().x + m_mainBtnTex.getSize().x) &&
		mousepos.y >= (m_mainBtn.getPosition().y) &&
		mousepos.y <= (m_mainBtn.getPosition().y + m_mainBtnTex.getSize().y) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_switchingScene = sceneswitch(true, "MenuScene");
	}
	if (mousepos.x >= (m_dungeonBtn.getPosition().x) &&
		mousepos.x <= (m_dungeonBtn.getPosition().x + m_dungeonBtnTex.getSize().x) &&
		mousepos.y >= (m_dungeonBtn.getPosition().y) &&
		mousepos.y <= (m_dungeonBtn.getPosition().y + m_dungeonBtnTex.getSize().y) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_switchingScene = sceneswitch(true, "DungeonScene");
	}
	if (mousepos.x >= (m_generateBtn.getPosition().x) &&
		mousepos.x <= (m_generateBtn.getPosition().x + m_generateBtnTex.getSize().x) &&
		mousepos.y >= (m_generateBtn.getPosition().y) &&
		mousepos.y <= (m_generateBtn.getPosition().y + m_generateBtnTex.getSize().y) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		ClearDrawables();
		RenderDungeon();
	}
}

void CellScene::Start()
{
	m_alive = true;
	SetupGraph();
}

void CellScene::Stop()
{
	m_alive = false;
	RestartScene();
	m_switchingScene = sceneswitch(false, "");
}

void CellScene::RestartScene()
{
	ClearDrawables();
	delete m_graph;
	m_graph = nullptr;
	delete m_translatedGraph;
	m_translatedGraph = nullptr;
}

std::vector<std::pair<std::string, Cave>> CellScene::LoadRules()
{
	std::vector<std::pair<std::string, Cave>> rules;
	std::queue<std::string> ruleID;

	std::ifstream file;
	file.open("Assets/CellScene/Graph/rules.txt");

	std::vector<std::string> data;
	std::string line;

	while (std::getline(file, line))
		data.push_back(line);

	file.close();

	for (int i = 0; i < data.size(); i++)
	{
		std::istringstream ss(data[i]);
		std::string line;

		std::vector<std::string> ruleData;
		while (std::getline(ss, line, '/'))
		{
			ruleData.push_back(line);
		}

		std::istringstream ssNodes(ruleData[1]);
		while (std::getline(ssNodes, line, ','))
		{
			ruleID.push(line);
		}
	}

	file.open("Assets/CellScene/Graph/nodes.txt");
	std::string data2;
	while (file >> data2)
	{
		ruleID.push(data2);
	}
	file.close();

	while (!ruleID.empty())
	{
		std::string front = ruleID.front();
		Cave c = Cave();
		if (front == "e")
		{
			c.m_position = sf::Vector2f(12, 12);
			c.m_rule = "smooth";
			c.m_chance = 30;
		}
		else if (front == "b")
		{
			c.m_rule = "smooth";
			c.m_chance = 30;
		}
		else if (front == "cnsrv_high")
		{
			c.m_rule = "conservative";
			c.m_chance = 37;
		}
		else if (front == "cnsrv_low")
		{
			c.m_rule = "conservative";
			c.m_chance = 30;
		}
		else if (front == "smth_high")
		{
			c.m_rule = "smooth";
			c.m_chance = 37;
		}
		else if (front == "smth_low")
		{
			c.m_rule = "smooth";
			c.m_chance = 30;
		}
		rules.push_back(std::make_pair(front, c));
		ruleID.pop();
	}

	return rules;
}

void CellScene::SetupGraph()
{
	int noOfNodes = 0;

	std::ifstream file;

	m_graph = new Graph<Cave, std::string>();

	file.open("Assets/CellScene/Graph/nodes.txt");
	std::string data;
	Cave r = Cave();
	
	while (file >> data)
	{
		m_graph->AddNode(data, r);
	}
	file.close();

	file.open("Assets/CellScene/Graph/arcs.txt");
	int from, to;
	while (file >> from >> to)
	{
		m_graph->AddArc(from, to, "");
	}
	file.close();
}

void CellScene::SetupGrammar()
{
	m_grammar = GrammarSystem<Cave, std::string>();
	m_grammar.CreateRules("Assets/CellScene/Graph/rules.txt");
}

void CellScene::RenderDungeon()
{
	m_translatedGraph = new Graph<Cave, std::string>(*m_graph);
	m_grammar.Translate(m_translatedGraph, LoadRules());

	std::queue<Node*> nodeQueue;
	Node* start = m_translatedGraph->m_nodes.front();
	start->m_marked = true;
	CreateRoom(start, nullptr, 0);
	int numberOfRooms = m_translatedGraph->m_nodes.size();
	int count = 2;
	nodeQueue.push(start);
	while (nodeQueue.size() != 0) //explore child nodes
	{
		std::list<Arc>::const_iterator iter = nodeQueue.front()->m_arcList.begin();
		std::list<Arc>::const_iterator endIter = nodeQueue.front()->m_arcList.end();

		for (; iter != endIter; iter++) {
			if ((*iter).m_node->m_marked == false) {
				// mark the node and add it to the queue.
				//(*iter).m_node->m_marked = true;
				CreateRoom((*iter).m_node, nodeQueue.front(), count);
				nodeQueue.push((*iter).m_node);
			}
		}
		if (count < numberOfRooms)
			count++;
		nodeQueue.front()->m_marked = true;
		nodeQueue.pop();
	}
}

void CellScene::ClearDrawables()
{
	int gridsSize = m_grids.size();
	for (int i = 0; i < gridsSize; i++)
	{
		m_grids.erase(m_grids.begin());
	}
}

void CellScene::CreateRoom(Node* node, Node* parent, int count)
{
	Grid grid;

	sf::Vector2f tilesize = sf::Vector2f(12, 12);
	int rows = 40;
	int cols = 30;

	int offsetX = tilesize.x * rows;
	int offsetY = tilesize.y * cols;

	if (node->m_name == "e")
	{
		grid = Grid(sf::Vector2f(12,12), node->m_data.m_position, rows, cols);
		RandomFill(grid, node->m_data.m_chance);
	}
	else
	{
		if (count == 2)
		{
			node->m_data.m_position = sf::Vector2f(parent->m_data.m_position.x + offsetX, parent->m_data.m_position.y);
		}
		else if (count == 4)
		{
			node->m_data.m_position = sf::Vector2f(parent->m_data.m_position.x - offsetX, parent->m_data.m_position.y);
		}
		else if (count == 3)
		{
			node->m_data.m_position = sf::Vector2f(parent->m_data.m_position.x, parent->m_data.m_position.y + offsetY);
		}

		grid = Grid(sf::Vector2f(12, 12), node->m_data.m_position, rows, cols);
		RandomFill(grid, node->m_data.m_chance);
	}

	const int numberOfEvolves = 1;
	for (int i = 0; i < numberOfEvolves; i++)
	{
		EvolveMap(grid, node->m_data.m_rule);
	}

	CreateExits(node, parent, grid);

	m_grids.push_back(grid);
}

void CellScene::CreateExits(Node *node, Node *parent, Grid &g)
{
	if (node->m_name == "e")
	{
		const int offset = g.GetNumberOfCols() * 0.2;
		const int middle = g.GetNumberOfRows() / 2;

		int pathPos = rand() % ((g.GetNumberOfCols() - 1) - offset) + offset;
		node->m_data.m_exitPos = pathPos;

		for (int i = g.GetNumberOfRows() - 1; i > middle; i--)
		{
			g.GetTiles()[i][pathPos].UnFillTile();
			g.GetTiles()[i][pathPos + 1].UnFillTile();
			g.GetTiles()[i][pathPos - 1].UnFillTile();
		}
	}
	else if (parent->m_name == "e")
	{
		node->m_data.m_exitPos = parent->m_data.m_exitPos;

		const int middle = g.GetNumberOfRows() / 2;

		for (int i = 0; i < middle; i++)
		{
			g.GetTiles()[i][node->m_data.m_exitPos].UnFillTile();
			g.GetTiles()[i][node->m_data.m_exitPos + 1].UnFillTile();
			g.GetTiles()[i][node->m_data.m_exitPos - 1].UnFillTile();
		}

		const int offset = g.GetNumberOfCols() * 0.2;
		const int middle2 = (g.GetNumberOfCols() / 2) - 5;

		int pathPos = rand() % ((g.GetNumberOfCols() - 1) - offset) + (offset * 2);
		node->m_data.m_exitPos = pathPos;

		for (int i = g.GetNumberOfCols() - 1; i > middle2; i--)
		{
			g.GetTiles()[pathPos][i].UnFillTile();
			g.GetTiles()[pathPos + 1][i].UnFillTile();
			g.GetTiles()[pathPos - 1][i].UnFillTile();
		}
	}
	else if (node->m_name == "b")
	{
		node->m_data.m_exitPos = parent->m_data.m_exitPos;
		const int middle = g.GetNumberOfCols() / 2;

		for (int i = g.GetNumberOfRows() - 1; i > middle; i--)
		{
			g.GetTiles()[i][node->m_data.m_exitPos].UnFillTile();
			g.GetTiles()[i][node->m_data.m_exitPos + 1].UnFillTile();
			g.GetTiles()[i][node->m_data.m_exitPos - 1].UnFillTile();
		}
	}
	else
	{
		node->m_data.m_exitPos = parent->m_data.m_exitPos;

		const int middle = g.GetNumberOfCols() / 2;

		for (int i = 0; i < middle; i++)
		{
			g.GetTiles()[node->m_data.m_exitPos][i].UnFillTile();
			g.GetTiles()[node->m_data.m_exitPos + 1][i].UnFillTile();
			g.GetTiles()[node->m_data.m_exitPos - 1][i].UnFillTile();
		}

		const int offset = g.GetNumberOfCols() * 0.2;
		const int middle2 = (g.GetNumberOfRows() / 2) + 5;

		int pathPos = rand() % ((g.GetNumberOfCols() - 1) - offset) + (offset);
		node->m_data.m_exitPos = pathPos;

		for (int i = 0; i < middle2; i++)
		{
			g.GetTiles()[i][pathPos].UnFillTile();
			g.GetTiles()[i][pathPos + 1].UnFillTile();
			g.GetTiles()[i][pathPos - 1].UnFillTile();
		}
	}
}

void CellScene::RandomFill(Grid & g, const int chance)
{
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
				if (col == middle)
					g.GetTiles()[row][col].UnFillTile();
				else if ((rand() % 101) < chance)
					g.GetTiles()[row][col].FillTile();
			}
		}
	}
}

void CellScene::EvolveMap(Grid &g, std::string rule)
{
	for (int row = 1; row <= g.GetNumberOfRows() - 1; row++)
	{
		for (int col = 1; col <= g.GetNumberOfCols() - 1; col++)
		{
			if (PlaceWallLogic(g, row, col, rule))
				g.GetTiles()[row][col].FillTile();
			else
				g.GetTiles()[row][col].UnFillTile();
		}
	}
}

bool CellScene::PlaceWallLogic(Grid &g, int row, int col, std::string rule)
{
	int numWalls = GetSurroundingWalls(g, row, col, 1, 1);
	int numWalls2 = GetSurroundingWalls(g, row, col, 2, 2);

	if (g.GetTiles()[row][col].IsFilled())
	{
		return (numWalls >= 3) ? true : false;
	}
	else
	{
		if (rule == "conservative")
		{
			if (numWalls >= 5 || numWalls2 <= 2)
				return true;
		}
		else if (rule == "smooth")
		{
			if (numWalls >= 5) {
				return true;
			}
		}
	}
	return false;
}

int CellScene::GetSurroundingWalls(Grid &g, int row, int col, int scopeX, int scopeY)
{
	int startX = row - scopeX;
	int startY = col - scopeY;
	int endX = row + scopeX;
	int endY = col + scopeY;

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

