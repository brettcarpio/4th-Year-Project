#ifndef DUNGEON_SCENE_H
#define DUNGEON_SCENE_H

#include "Scene.h"
#include "GrammarSystem.h"
#include "Graph.h"
#include "Grid.h"

#include <fstream>

struct Room
{
	sf::Texture m_tex;
	sf::Sprite m_sprite;
	char m_dir;
	std::queue<char> m_out;
};

class DungeonScene : public Scene {
public:
	typedef GraphArc<Room, std::string> Arc;
	typedef GraphNode<Room, std::string> Node;

	DungeonScene(sf::RenderWindow& window);
	~DungeonScene();

	void Update(sf::Time dt);
	void Render(sf::RenderWindow & window);
	void HandleInput(sf::Event e);
	void Start();
	void Stop();

private:
	void SetupGraph();
	void SetupGrammar();
	void RenderDungeon();
	void ClearDrawables();
	void RestartScene();
	void CreateRoom(Node* node, Node* parent);
	void SetNodeData(Node* node, Node* parent);
	std::vector<std::pair<std::string, Room>> LoadRules();

private:
	GrammarSystem<Room, std::string> m_grammar;
	Graph<Room, std::string>* m_graph;
	Graph<Room, std::string>* m_translatedGraph;

	std::vector<Node*> m_rooms;
	Grid m_grid;
};

#endif // !DUNGEON_SCENE_H
