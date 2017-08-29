#include "..\include\DungeonScene.h"

DungeonScene::DungeonScene(sf::RenderWindow& window) : Scene("DungeonScene", false, sceneswitch(false, ""))
{
	SetupGraph();
	SetupGrammar();
	m_grid = Grid(sf::Vector2f(16, 16), sf::Vector2f(window.getSize()));
}

DungeonScene::~DungeonScene()
{
	RestartScene();
}

void DungeonScene::Update(sf::Time dt)
{
}

void DungeonScene::Render(sf::RenderWindow & window)
{
	for (Node* r : m_rooms)
		window.draw(r->m_data.m_sprite);

	m_grid.Render(window);
}

void DungeonScene::HandleInput(sf::Event e)
{
	if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Num1))
	{
		m_switchingScene = sceneswitch(true, "MenuScene");
	}
	else if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Num3))
	{
		m_switchingScene = sceneswitch(true, "CellScene");
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
}

void DungeonScene::Start()
{
	m_alive = true;
	SetupGraph();
	SetupGrammar();
}

void DungeonScene::Stop()
{
	m_alive = false; 
	m_switchingScene = sceneswitch(false, "");
	RestartScene();
}

void DungeonScene::ClearDrawables()
{
	int roomSize = m_rooms.size();
	for (int i = 0; i < roomSize; i++)
	{
		m_rooms.erase(m_rooms.begin());
	}
	delete m_translatedGraph;
	m_translatedGraph = nullptr;
}

void DungeonScene::RestartScene()
{
	ClearDrawables();
	delete m_graph;
	m_graph = nullptr;
	delete m_translatedGraph;
	m_translatedGraph = nullptr;
	m_grid.SetVisible(false);
}

void DungeonScene::RenderDungeon()
{
	m_translatedGraph = new Graph<Room, std::string>(*m_graph);
	m_grammar.Translate(m_translatedGraph);
	
	std::queue<Node*> nodeQueue;
	Node* start = m_translatedGraph->m_nodes.front();

	nodeQueue.push(start);

	start->m_marked = true;
	static const char direction[] = "URDL";
	int stringLength = sizeof(direction) - 1;
	start->m_data.m_dir = direction[rand() % stringLength];
	start->m_data.m_tex.loadFromFile("Assets/DungeonScene/Assets/" + start->m_name + start->m_data.m_dir + ".png");
	start->m_data.m_sprite.setTexture(start->m_data.m_tex);
	start->m_data.m_sprite.setPosition(sf::Vector2f(400, 256));

	m_rooms.push_back(start);

	while (nodeQueue.size() != 0) //explore child nodes
	{
		std::list<Arc>::const_iterator iter = nodeQueue.front()->m_arcList.begin();
		std::list<Arc>::const_iterator endIter = nodeQueue.front()->m_arcList.end();

		for (; iter != endIter; iter++) {
			if ((*iter).m_node->m_marked == false) {
				// mark the node and add it to the queue.
				//(*iter).m_node->m_marked = true;
				CreateRoom((*iter).m_node, nodeQueue.front());
				nodeQueue.push((*iter).m_node);
			}
		}

		nodeQueue.front()->m_marked = true;
		nodeQueue.pop();
	}
}

void DungeonScene::CreateRoom(Node * node, Node* parent)
{
	if (parent != nullptr)
	{
		SetNodeData(node, parent);
	}

	if (node->m_name == "frk")
	{
		if (node->m_data.m_dir == 'U')
		{
			node->m_data.m_out.push('L');
			node->m_data.m_out.push('R');
		}
		else if (node->m_data.m_dir == 'R')
		{
			node->m_data.m_out.push('D');
			node->m_data.m_out.push('U');
		}
		else if (node->m_data.m_dir == 'D')
		{
			node->m_data.m_out.push('L');
			node->m_data.m_out.push('R');
		}
		else if (node->m_data.m_dir == 'L')
		{
			node->m_data.m_out.push('U');
			node->m_data.m_out.push('D');
		}
	}
	else if (node->m_name == "cr")
	{
		if (node->m_data.m_dir == 'U')
		{
			node->m_data.m_out.push('L');
			node->m_data.m_out.push('U');
			node->m_data.m_out.push('R');
		}
		else if (node->m_data.m_dir == 'R')
		{
			node->m_data.m_out.push('D');
			node->m_data.m_out.push('R');
			node->m_data.m_out.push('U');

		}
		else if (node->m_data.m_dir == 'D')
		{
			node->m_data.m_out.push('R');
			node->m_data.m_out.push('D');
			node->m_data.m_out.push('L');
		}
		else if (node->m_data.m_dir == 'L')
		{
			node->m_data.m_out.push('D');
			node->m_data.m_out.push('L');
			node->m_data.m_out.push('U');
		}
	}

	

	m_rooms.push_back(node);
}

void DungeonScene::SetNodeData(Node * node, Node * parent)
{
	sf::Vector2f up = sf::Vector2f(0, -1.f *(parent->m_data.m_tex.getSize().y));
	sf::Vector2f right = sf::Vector2f(parent->m_data.m_tex.getSize().x, 0);
	sf::Vector2f down = sf::Vector2f(0, (parent->m_data.m_tex.getSize().y));
	sf::Vector2f left = sf::Vector2f(-1.f *(parent->m_data.m_tex.getSize().x), 0);

	if (parent->m_name == "e")
	{
		if (parent->m_data.m_dir == 'U')
			node->m_data.m_dir = 'D';
		else if (parent->m_data.m_dir == 'R')
			node->m_data.m_dir = 'L';
		else if (parent->m_data.m_dir == 'D')
			node->m_data.m_dir = 'U';
		else if (parent->m_data.m_dir == 'L')
			node->m_data.m_dir = 'R';

		node->m_data.m_tex.loadFromFile("Assets/DungeonScene/Assets/" + node->m_name + node->m_data.m_dir + ".png");
		node->m_data.m_sprite.setTexture(node->m_data.m_tex);
	}
	else if (parent->m_name == "rt")
	{
		if (parent->m_data.m_dir == 'U')
			node->m_data.m_dir = 'R';
		else if (parent->m_data.m_dir == 'R')
			node->m_data.m_dir = 'D';
		else if (parent->m_data.m_dir == 'D')
			node->m_data.m_dir = 'L';
		else if (parent->m_data.m_dir == 'L')
			node->m_data.m_dir = 'U';

		node->m_data.m_tex.loadFromFile("Assets/DungeonScene/Assets/" + node->m_name + node->m_data.m_dir + ".png");
		node->m_data.m_sprite.setTexture(node->m_data.m_tex);
		
	}
	else if (parent->m_name == "cr")
	{
		node->m_data.m_dir = parent->m_data.m_out.front();
		parent->m_data.m_out.pop();
		node->m_data.m_tex.loadFromFile("Assets/DungeonScene/Assets/" + node->m_name + node->m_data.m_dir + ".png");
		node->m_data.m_sprite.setTexture(node->m_data.m_tex);
	}
	else if (parent->m_name == "frk")
	{
		node->m_data.m_dir = parent->m_data.m_out.front();
		parent->m_data.m_out.pop();
		node->m_data.m_tex.loadFromFile("Assets/DungeonScene/Assets/" + node->m_name + node->m_data.m_dir + ".png");
		node->m_data.m_sprite.setTexture(node->m_data.m_tex);
	}
	else if (parent->m_name == "sp")
	{
		if (parent->m_data.m_dir == 'U')
			node->m_data.m_dir = 'U';
		else if (parent->m_data.m_dir == 'R')
			node->m_data.m_dir = 'R';
		else if (parent->m_data.m_dir == 'D')
			node->m_data.m_dir = 'D';
		else if (parent->m_data.m_dir == 'L')
			node->m_data.m_dir = 'L';

		node->m_data.m_tex.loadFromFile("Assets/DungeonScene/Assets/" + node->m_name + node->m_data.m_dir + ".png");
		node->m_data.m_sprite.setTexture(node->m_data.m_tex);
	}

	if (node->m_data.m_dir == 'U')
		node->m_data.m_sprite.setPosition(parent->m_data.m_sprite.getPosition() + down);
	else if (node->m_data.m_dir == 'R')
		node->m_data.m_sprite.setPosition(parent->m_data.m_sprite.getPosition() + left);
	else if (node->m_data.m_dir == 'D')
		node->m_data.m_sprite.setPosition(parent->m_data.m_sprite.getPosition() + up);
	else if (node->m_data.m_dir == 'L')
		node->m_data.m_sprite.setPosition(parent->m_data.m_sprite.getPosition() + right);
}


void DungeonScene::SetupGraph()
{
	int noOfNodes = 0;

	std::ifstream file;

	m_graph = new Graph<Room, std::string>();

	file.open("Assets/DungeonScene/Graph/nodes.txt");
	std::string data;
	while (file >> data)
	{
		Room r = Room();
		m_graph->AddNode(data, r);
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

void DungeonScene::SetupGrammar()
{
	m_grammar = GrammarSystem<Room, std::string>();
	m_grammar.CreateRules("Assets/DungeonScene/Graph/rules.txt");
}