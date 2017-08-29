#include "CellScene.h"

CellScene::CellScene(sf::RenderWindow & window) : Scene("CellScene", false, sceneswitch(false, ""))
{
	SetupGraph();
	SetupGrammar();
	m_grid = Grid(sf::Vector2f(16, 16), sf::Vector2f(window.getSize()));
	m_grid.SetVisible(true);
}

CellScene::~CellScene()
{
}

void CellScene::Update(sf::Time dt)
{
}

void CellScene::Render(sf::RenderWindow & window)
{
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
