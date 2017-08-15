#ifndef DUNGEON_SCENE_H
#define DUNGEON_SCENE_H

#include "Scene.h"
#include "GrammarSystem.h"
#include "Graph.h"

#include <fstream>


class DungeonScene : public Scene {
public:
	DungeonScene(sf::RenderWindow& window);
	~DungeonScene();

	void Update(sf::Time dt);
	void Render(sf::RenderWindow & window);
	void HandleInput(sf::Event e);

private:
	void SetupGraph();

private:
	GrammarSystem m_grammar;
	Graph<std::string, std::string> m_graph;
};

#endif // !DUNGEON_SCENE_H
