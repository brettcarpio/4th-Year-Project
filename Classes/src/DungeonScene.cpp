#include "..\include\DungeonScene.h"

DungeonScene::DungeonScene(sf::RenderWindow& window) : Scene("DungeonScene", false, sceneswitch(false, ""))
{
	SetupGraph();
	SetupGrammar();
	m_grid = Grid(sf::Vector2f(16, 16), sf::Vector2f(0, 0), (window.getSize().x / 16), (window.getSize().y / 16));

	if (!m_logoTexture.loadFromFile("Assets/DungeonScene/Assets/logo.png"))
		std::cout << "logo not loaded!" << std::endl;
	if (!m_caveBtnTex.loadFromFile("Assets/DungeonScene/Assets/Cave_btn.png"))
		std::cout << "C.A button not loaded!" << std::endl;
	if (!m_mainBtnTex.loadFromFile("Assets/DungeonScene/Assets/main_btn.png"))
		std::cout << "main button not loaded!" << std::endl;
	if (!m_generateBtnTex.loadFromFile("Assets/DungeonScene/Assets/generate.png"))
		std::cout << "generate button not loaded!" << std::endl;

	m_mainBtn.setTexture(m_mainBtnTex);
	m_mainBtn.setPosition(window.getSize().x - 350, 550);

	m_caveBtn.setTexture(m_caveBtnTex);
	m_caveBtn.setPosition(window.getSize().x - 350, 650);

	m_logo.setTexture(m_logoTexture);
	m_logo.setPosition(m_mainBtn.getPosition().x - 50, 25);

	m_generateBtn.setTexture(m_generateBtnTex);
	m_generateBtn.setPosition(window.getSize().x - 350, 250);

	m_sprites.push_back(m_logo);
	m_sprites.push_back(m_mainBtn);
	m_sprites.push_back(m_generateBtn);
	m_sprites.push_back(m_caveBtn);

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

	for (sf::Sprite s : m_sprites)
		window.draw(s);

	m_grid.Render(window);
	mousepos = sf::Mouse::getPosition(window);

	
}

void DungeonScene::HandleInput(sf::Event e)
{
	if (mousepos.x >= (m_mainBtn.getPosition().x) &&
		mousepos.x <= (m_mainBtn.getPosition().x + m_mainBtnTex.getSize().x) &&
		mousepos.y >= (m_mainBtn.getPosition().y) &&
		mousepos.y <= (m_mainBtn.getPosition().y + m_mainBtnTex.getSize().y) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_switchingScene = sceneswitch(true, "MenuScene");
	}
	if (mousepos.x >= (m_caveBtn.getPosition().x) &&
		mousepos.x <= (m_caveBtn.getPosition().x + m_caveBtnTex.getSize().x) &&
		mousepos.y >= (m_caveBtn.getPosition().y) &&
		mousepos.y <= (m_caveBtn.getPosition().y + m_caveBtnTex.getSize().y) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_switchingScene = sceneswitch(true, "CellScene");
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

void DungeonScene::Start()
{
	m_alive = true;
	SetupGraph();
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
}

void DungeonScene::RenderDungeon()
{
	m_translatedGraph = new Graph<Room, std::string>(*m_graph);
	m_grammar.Translate(m_translatedGraph, LoadRules());
	
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

std::vector<std::pair<std::string, Room>> DungeonScene::LoadRules()
{
	std::vector<std::pair<std::string, Room>> rules;
	std::queue<std::string> ruleID;

	return rules;
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