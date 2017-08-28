#include "..\include\DungeonScene.h"

DungeonScene::DungeonScene(sf::RenderWindow& window) : Scene("DungeonScene", false, sceneswitch(false, ""))
{
	SetupGraph();
	SetupGrammar();
}

DungeonScene::~DungeonScene()
{
	ClearDrawables();
}

void DungeonScene::Update(sf::Time dt)
{
}

void DungeonScene::Render(sf::RenderWindow & window)
{
	for (Room r : m_rooms)
		window.draw(r.m_sprite);
}

void DungeonScene::HandleInput(sf::Event e)
{
	if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Num1))
	{
		m_switchingScene = sceneswitch(true, "MenuScene");
	}
	if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Space))
	{
		ClearDrawables();
		RenderDungeon();
	}
}

void DungeonScene::ClearDrawables()
{
	for (int i = 0; i < m_rooms.size(); i++)
	{
		delete m_rooms[i].m_tex;
		m_rooms[i].m_tex = nullptr;
		m_rooms.erase(m_rooms.begin() + i);
	}
}

void DungeonScene::RenderDungeon()
{
	Graph<std::string, std::string> temp = m_grammar.Translate(m_graph);
	
	std::queue<Node*> nodeQueue;
	Node* start = temp.m_nodes.front();

	nodeQueue.push(start);
	start->m_marked = true;
	CreateRoom(start, 0);

	while (nodeQueue.size() != 0)
	{
		std::list<Arc>::const_iterator iter = nodeQueue.front()->m_arcList.begin();
		std::list<Arc>::const_iterator endIter = nodeQueue.front()->m_arcList.end();

		for (; iter != endIter; iter++) {
			if ((*iter).m_node->m_marked == false) {
				// mark the node and add it to the queue.
				(*iter).m_node->m_marked = true;
				CreateRoom((*iter).m_node, nodeQueue.front());
				nodeQueue.push((*iter).m_node);
			}
		}

		nodeQueue.pop();
	}
	
}

void DungeonScene::CreateRoom(Node * node, Node* parent)
{
	static const char direction[] = "URDL";
	int stringLength = sizeof(direction) - 1;
	Room r = Room();

	if (node->m_data == "e" && parent == nullptr)
	{
		char dir = direction[rand() % stringLength];
		r.m_tex = new sf::Texture;
		r.m_tex->loadFromFile("Assets/DungeonScene/Assets/" + node->m_data + dir + ".png");
		r.m_sprite.setTexture(*r.m_tex);
		r.m_sprite.setPosition(sf::Vector2f(200, 200));
	}
	
	else if (parent->m_data == "e")
	{

	}

	m_rooms.push_back(r);
}

char DungeonScene::GetDirection(std::string name)
{
	for (char &c : name)
	{
		if (isupper(c))
		{
			return c;
		}
	}
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

void DungeonScene::SetupGrammar()
{
	m_grammar = GrammarSystem<std::string, std::string>();
	m_grammar.CreateRules("Assets/DungeonScene/Graph/rules.txt");
}