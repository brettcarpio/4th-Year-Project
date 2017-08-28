#ifndef DUNGEON_SCENE_H
#define DUNGEON_SCENE_H

#include "Scene.h"
#include "GrammarSystem.h"
#include "Graph.h"

#include <fstream>

class DungeonScene : public Scene {
public:
	typedef GraphArc<std::string, std::string> Arc;
	typedef GraphNode<std::string, std::string> Node;

	DungeonScene(sf::RenderWindow& window);
	~DungeonScene();

	void Update(sf::Time dt);
	void Render(sf::RenderWindow & window);
	void HandleInput(sf::Event e);

private:
	void SetupGraph();
	void SetupGrammar();
	void RenderDungeon();
	void ClearDrawables();
	void CreateRoom(Node* node, Node* parent);
	char GetDirection(std::string name);

private:
	struct Room
	{
		sf::Texture* m_tex;
		sf::Sprite m_sprite;
	};
	GrammarSystem<std::string, std::string> m_grammar;
	Graph<std::string, std::string> m_graph;

	std::vector<Room> m_rooms;
};

#endif // !DUNGEON_SCENE_H
