#ifndef CELL_SCENE_H
#define CELL_SCENE_H

#include "Scene.h"
#include "GrammarSystem.h"
#include "Graph.h"

#include <fstream>

class CellScene : public Scene {
public:
	typedef GraphArc<int, std::string> Arc;
	typedef GraphNode<int, std::string> Node;

	CellScene(sf::RenderWindow& window);
	~CellScene();

	void Update(sf::Time dt);
	void Render(sf::RenderWindow & window);
	void HandleInput(sf::Event e);
	void Start();
	void Stop();

private:
	void SetupGraph();
	void SetupGrammar();

private:
	GrammarSystem<int, std::string> m_grammar;
	Graph<int, std::string>* m_graph;
	Graph<int, std::string>* m_translatedGraph;

};

#endif // !CELL_SCENE_H
