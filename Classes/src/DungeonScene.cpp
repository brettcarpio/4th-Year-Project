#include "..\include\DungeonScene.h"

DungeonScene::DungeonScene(sf::RenderWindow& window) : Scene("DungeonScene", false, sceneswitch(false, ""))
{
	m_grammar = GrammarSystem();
	

	SetupGraph();

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
	if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::A))
	{
		m_grammar.ConvertToLowercase("TESt123 house TREE food");
	}
}

void DungeonScene::SetupGraph()
{
	int noOfNodes = 0;

	std::ifstream file;
	file.open("Assets/DungeonScene/Graph/nodes.txt");
	std::string line;
	while(std::getline(file, line))
		noOfNodes++;
	m_graph = Graph<std::string, std::string>(noOfNodes);
	file.close();

	file.open("Assets/DungeonScene/Graph/nodes.txt");
	int index = 0;
	std::string data;
	while (file >> data &&  index < noOfNodes)
	{
		m_graph.AddNode(data, index);
		index++;
	}
	file.close();
}