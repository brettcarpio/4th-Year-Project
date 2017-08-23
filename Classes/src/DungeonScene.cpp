#include "..\include\DungeonScene.h"

DungeonScene::DungeonScene(sf::RenderWindow& window) : Scene("DungeonScene", false, sceneswitch(false, ""))
{
	SetupGraph();
	TranslateGraph();
}

DungeonScene::~DungeonScene()
{
}

void DungeonScene::Update(sf::Time dt)
{
}

void DungeonScene::Render(sf::RenderWindow & window)
{
}

void DungeonScene::HandleInput(sf::Event e)
{
	if ((e.type == sf::Event::KeyPressed) && (sf::Keyboard::Num1))
	{
		m_switchingScene = sceneswitch(true, "MenuScene");
	}
	/*if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::A))
	{
		m_grammar.ConvertToLowercase("TESt123 house TREE food");
	}*/
}

void DungeonScene::SetupGraph()
{
	int noOfNodes = 0;

	std::ifstream file;

	m_graph = Graph<std::string, std::string>();

	file.open("Assets/DungeonScene/Graph/nodes.txt");
	std::string data;
	while (file >> data)
	{
		m_graph.AddNode(data);
	}
	file.close();

	file.open("Assets/DungeonScene/Graph/arcs.txt");
	int from, to;
	while (file >> from >> to)
	{
		m_graph.AddArc(from, to, "");
	}
	file.close();
}

void DungeonScene::TranslateGraph()
{
	m_grammar = GrammarSystem<std::string, std::string>();
	m_grammar.CreateRules("Assets/DungeonScene/Graph/rules.txt");
	Graph<std::string, std::string> temp = m_grammar.Translate(m_graph);
}