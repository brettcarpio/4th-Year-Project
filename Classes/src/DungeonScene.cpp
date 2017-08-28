#include "..\include\DungeonScene.h"

DungeonScene::DungeonScene(sf::RenderWindow& window) : Scene("DungeonScene", false, sceneswitch(false, ""))
{
	SetupGraph();
	SetupGrammar();
}

DungeonScene::~DungeonScene()
{
	ClearDrawables();
	delete m_graph;
	m_graph = nullptr;
	delete m_translatedGraph;
	m_translatedGraph = nullptr;
}

void DungeonScene::Update(sf::Time dt)
{
}

void DungeonScene::Render(sf::RenderWindow & window)
{
	for (Node* r : m_rooms)
		window.draw(r->m_data.m_sprite);
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
		m_rooms.erase(m_rooms.begin() + i);
	}
}

void DungeonScene::RenderDungeon()
{
	m_translatedGraph = m_grammar.Translate(m_graph);
	
	std::queue<Node*> nodeQueue;
	Node* start = m_translatedGraph->m_nodes.front();

	nodeQueue.push(start);

	start->m_marked = true;
	static const char direction[] = "URDL";
	int stringLength = sizeof(direction) - 1;
	start->m_data.m_dir = direction[rand() % stringLength];
	start->m_data.m_tex.loadFromFile("Assets/DungeonScene/Assets/" + start->m_name + start->m_data.m_dir + ".png");
	start->m_data.m_sprite.setTexture(start->m_data.m_tex);
	start->m_data.m_sprite.setPosition(sf::Vector2f(400, 200));

	m_rooms.push_back(start);

	while (nodeQueue.size() != 0) //explore child nodes
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
	if (parent->m_name == "frk")
	{
		if (parent->m_data.m_dir == 'U')
		{
			parent->m_data.m_out.push('L');
			parent->m_data.m_out.push('R');
		}
		else if (parent->m_data.m_dir == 'R')
		{
			parent->m_data.m_out.push('U');
			parent->m_data.m_out.push('D');
		}
		else if (parent->m_data.m_dir == 'D')
		{
			parent->m_data.m_out.push('R');
			parent->m_data.m_out.push('L');
		}
		else if (parent->m_data.m_dir == 'L')
		{
			parent->m_data.m_out.push('D');
			parent->m_data.m_out.push('U');
		}
	}
	else if (parent->m_name == "cr")
	{
		if (parent->m_data.m_dir == 'U')
		{
			parent->m_data.m_out.push('R');
			parent->m_data.m_out.push('L');
			parent->m_data.m_out.push('D');
		}
		else if (parent->m_data.m_dir == 'R')
		{
			parent->m_data.m_out.push('D');
			parent->m_data.m_out.push('U');
			parent->m_data.m_out.push('L');

		}
		else if (parent->m_data.m_dir == 'D')
		{
			parent->m_data.m_out.push('L');
			parent->m_data.m_out.push('R');
			parent->m_data.m_out.push('U');
		}
		else if (parent->m_data.m_dir == 'L')
		{
			parent->m_data.m_out.push('U');
			parent->m_data.m_out.push('D');
			parent->m_data.m_out.push('R');
		}
	}

	if (parent != nullptr) 
	{
		SetNodeData(node, parent);
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
			node->m_data.m_dir = 'U';
		else if (parent->m_data.m_dir == 'D')
			node->m_data.m_dir = 'L';
		else if (parent->m_data.m_dir == 'L')
			node->m_data.m_dir = 'D';

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